#pragma once
#include "SDL.h"
#include "..\maths\Vector2D.h"

class RigidBody
{
public:
	RigidBody();
	RigidBody(Vector2D position, Vector2D velocity, float mass, bool gravity);
	~RigidBody();
	void Initialise();
	void Update(float delta, bool collided);
	void Render(SDL_Renderer* renderer, bool debug);
	void ApplyForce(Vector2D force);
	void SetVelocity(Vector2D force);
	Vector2D GetVelocity(); 
	void SetPosition(Vector2D pos);
	Vector2D GetPosition();
	void ApplyGravity(float delta);
	void SetFixed(bool fixed);
	void SetGravityEffected(bool grav);
	void MoveObject(float x, float y);


	float		_mass = 5.0f; 
	bool		_onFloor;

private:
	Vector2D	_position;
	Vector2D	_velocity;
	bool		_gravityEffected;
	bool		_fixed; 
};

