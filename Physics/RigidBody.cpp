#include "RigidBody.h"

RigidBody::RigidBody()
{
	_velocity = Vector2D(0, 0);
	_position = Vector2D(0, 0);
	_gravityEffected = false;
	_fixed = false; 
	_onFloor = false;
	_mass = 10.0f;
}

RigidBody::RigidBody(Vector2D position, Vector2D velocity, float mass, bool gravity)
{
	_mass = mass; 
	_fixed = false; 
	_onFloor = false;
	_velocity = velocity;
	_position = position;
	_gravityEffected = gravity;
}


RigidBody::~RigidBody()
{
}

void RigidBody::Initialise()
{
}

void RigidBody::Update(float delta, bool collided)
{
	if (_gravityEffected == true)
	{
		ApplyGravity(delta);
	}
	_position = _position + _velocity;
}

//Renders a small dot on the screen in the center of the shape if the debug mode is on
void RigidBody::Render(SDL_Renderer* renderer, bool debug)
{
	if (debug)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
		int x = _position.GetX();
		int y = _position.GetY();
		SDL_RenderDrawLine(renderer, x - 1, y - 1, x + 1, y - 1);
		SDL_RenderDrawLine(renderer, x + 1, y - 1, x + 1, y + 1);
		SDL_RenderDrawLine(renderer, x + 1, y + 1, x - 1, y + 1);
		SDL_RenderDrawLine(renderer, x - 1, y + 1, x - 1, y - 1);

	}
}

//Applies a force by adding the velocity
void RigidBody::ApplyForce(Vector2D force)
{
	_velocity = _velocity + force; 
}

//Replaces the velocity with the supplied value
void RigidBody::SetVelocity(Vector2D force)
{
	_velocity = force; 
}

//Moves the position of the rigidbody to where specified
void RigidBody::SetPosition(Vector2D pos)
{
	_position = pos;
}

Vector2D RigidBody::GetPosition()
{
	return _position; 
}

void RigidBody::ApplyGravity(float delta)
{
	Vector2D temp = Vector2D(0, -9.81f);
	temp.SetY(temp.GetY() * delta);
	_velocity + temp;
	temp.~Vector2D();
}

void RigidBody::SetFixed(bool fixed)
{
	_fixed = fixed; 
}

void RigidBody::SetGravityEffected(bool grav)
{
	_gravityEffected = grav;
}

Vector2D RigidBody::GetVelocity()
{
	return _velocity;
}

//Moves the object by specified ammounts
void RigidBody::MoveObject(float x, float y)
{
	_position = Vector2D(_position.GetX() + x, _position.GetY() + y);
}