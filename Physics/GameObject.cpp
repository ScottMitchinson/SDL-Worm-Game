#include "GameObject.h"

GameObject::GameObject(ObjectType type, Vector2D position, const char* texPath, Vector2D *vects, SDL_Renderer* renderer)
{
	_type = type;
	_renderer = renderer;
	_shape = Shape(vects);
	_rigidBody = RigidBody(position, Vector2D(0, 0), 10.0f, false); 
	_texture = new Texture(_renderer);
	_texture->LoadFromFile(texPath);
	
	if (_type == PROJECTILE)
	{
		_rigidBody.SetGravityEffected(true);
	}
	
}

GameObject::GameObject(ObjectType type, Vector2D position, const char* texPath, Vector2D *vects, std::vector<Node*> nodePath, SDL_Renderer* renderer, Health* health)
{
	_type = type;
	_renderer = renderer;
	_shape = Shape(vects);
	_rigidBody = RigidBody(position, Vector2D(0, 0), 10.0f, false);
	_texture = new Texture(_renderer);
	_texture->LoadFromFile(texPath);
	_health = health;

	if (_type == ENEMY)
	{
		_plan = new PathPlanning(nodePath);
		_rigidBody.SetVelocity(_plan->FollowPath(position));
		_rigidBody.SetGravityEffected(false);
	}
}

GameObject::~GameObject()
{
	_texture->Destroy();
}

bool GameObject::Initialise()
{
	return false;
}

void GameObject::Update(float delta)
{	
	if (_type == ENEMY && _shape._collided == false)
	{
		if (_rigidBody.GetPosition().GetX() == 1092 && _rigidBody.GetPosition().GetY() == 300)
		{
			_health->Hit();
			_deleted = true;
		}
		else
		{
			_rigidBody.SetVelocity(_plan->FollowPath(_rigidBody.GetPosition()));

		}
	}
	_rigidBody.Update(delta, _shape._collided);
}

void GameObject::Render(bool debug)
{
	_texture->Render(_rigidBody.GetPosition().GetX(), 
					 _rigidBody.GetPosition().GetY(), 
					 _texture->getWidth(), 
					 _texture->getHeight());
	_shape.Render(_rigidBody.GetPosition(), _renderer, false, debug);
	_rigidBody.Render(_renderer, debug);
}

void GameObject::Destroy()
{
	_texture->Destroy();
}

void GameObject::SquareCollides(GameObject* obj, GameObject* objTwo)
{
	if (Collided(obj, objTwo, Vector2D(0, 1)) && Collided(obj, objTwo, Vector2D(1, 0)))
	{
		float newVelX1, newVelY1, newVelX2, newVelY2;
		float objOneX = obj->_rigidBody.GetVelocity().GetX();
		float objOneY = obj->_rigidBody.GetVelocity().GetY();
		float objTwoX = objTwo->_rigidBody.GetVelocity().GetX();
		float objTwoY = objTwo->_rigidBody.GetVelocity().GetY();
		float massOne = obj->_rigidBody._mass;
		float massTwo = objTwo->_rigidBody._mass;

		newVelX1 = ((objOneX * (massOne - massTwo)) + (2 * (massTwo * objTwoX))) / (massOne + massTwo);
		newVelY1 = ((objOneY * (massOne - massTwo)) + (2 * (massTwo * objTwoY))) / (massOne + massTwo);
		newVelX2 = ((objTwoX * (massTwo - massOne)) + (2 * (massOne * objOneX))) / (massOne + massTwo);
		newVelY2 = ((objTwoY * (massTwo - massOne)) + (2 * (massOne * objOneY))) / (massOne + massTwo);

		obj->_rigidBody.SetVelocity(Vector2D(newVelX1 * obj->_shape._bounce, newVelY1* obj->_shape._bounce));
		objTwo->_rigidBody.SetVelocity(Vector2D(newVelX2* objTwo->_shape._bounce, newVelY2* objTwo->_shape._bounce));

		if (obj->_type == ENEMY)
		{
			obj->_shape._collided = true;
			obj->_rigidBody.SetGravityEffected(true);
		}

		if (objTwo->_type == ENEMY)
		{
			objTwo->_shape._collided = true;
			objTwo->_rigidBody.SetGravityEffected(true);
		}

		if (obj->_type == PROJECTILE)
		{
			obj->_deleted = true;
		}

		if (objTwo->_type == PROJECTILE)
		{
			objTwo->_deleted = true;
		}			
			

		if (obj->_type == OTHER)
		{
			obj->_shape._collided = true;
			obj->_rigidBody.SetGravityEffected(true);
		}

		if (objTwo->_type == OTHER)
		{
			objTwo->_rigidBody.SetGravityEffected(true);
			objTwo->_shape._collided = true;
		}

		if (obj->_rigidBody.GetPosition().GetY() > objTwo->_rigidBody.GetPosition().GetY())
		{
			while (Collided(obj, objTwo, Vector2D(0, 1)) && Collided(obj, objTwo, Vector2D(0, 1)))
			{
				objTwo->_rigidBody.MoveObject(0, -1);
			}
			objTwo->_rigidBody.MoveObject(0, 1);
		}
		else
		{
			while (Collided(obj, objTwo, Vector2D(0, 1)) && Collided(obj, objTwo, Vector2D(0, 1)))
			{
				obj->_rigidBody.MoveObject(0, -1);
			}
			obj->_rigidBody.MoveObject(0, 1);
		}
	}
}

bool GameObject::Collided(GameObject* obj, GameObject* objTwo, Vector2D axis)
{
	MinMax a = objTwo->_shape.GetInterval(axis, objTwo->_rigidBody.GetPosition());
	MinMax b = obj->_shape.GetInterval(axis, obj->_rigidBody.GetPosition());

	if ((b.min <= a.max) && (a.min <= b.max))
	{
		return true;
	}
	else
	{
		return false;
	}
}