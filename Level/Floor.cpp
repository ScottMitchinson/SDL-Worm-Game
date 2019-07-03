#include "Floor.h"

Floor::Floor(unsigned int height, const char* texture, SDL_Renderer* renderer)
{
	_renderer = renderer;
	_texture = new Texture(_renderer);
	_texture->LoadFromFile(texture);
	float halfHeight = height / 2;
	_texPrintLocation = Vector2D(0, 1080 - height);
	Vector2D floor[] = {
		Vector2D(-960, -halfHeight    ), Vector2D( 960, -halfHeight    ),
		Vector2D( 960,  halfHeight - 1), Vector2D(-960,  halfHeight - 1)
	};
	_centre = Vector2D(960, 1080 - (height / 2));
	_floor = new Shape(floor);
}

Floor::~Floor()
{
}

void Floor::Render(bool debug)
{
	_texture->Render(_centre.GetX(), _centre.GetY(), _texture->getWidth(), _texture->getHeight());
	_floor->Render(_centre, _renderer, false, debug);
}

//uses SAT to determine if any of the objects have hit the floor
void Floor::SquareCollides(ObjectList* list)
{
	for (GameObject* object: list->_objects)
	{
		if (Collided(object))
		{
			object->_rigidBody._onFloor = true;
			object->_shape.SetCollided(true);
			float yVel = object->_rigidBody.GetVelocity().GetY();
			yVel = yVel * _bounce;
			yVel = -yVel;
			float xVel = object->_rigidBody.GetVelocity().GetX();
			xVel = xVel * _friction;
			object->_rigidBody.SetVelocity(Vector2D(xVel, yVel));
		}
		else
		{
			object->_rigidBody._onFloor = false;
		}
		
		if (object->_rigidBody._onFloor == true)
		{
			while (Collided(object) == true)
			{
				object->_rigidBody.MoveObject(0, -1);
			}
			object->_rigidBody.MoveObject(0, 1);
		}
	}
}

bool Floor::Collided(GameObject* obj)
{
	MinMax a = _floor->GetInterval(Vector2D(0, 1), _centre);
	MinMax b = obj->_shape.GetInterval(Vector2D(0, 1), obj->_rigidBody.GetPosition());

	if ((b.min <= a.max) && (a.min <= b.max))
	{
		return true;
	}
	else
	{
		return false;
	}
}