#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "RigidBody.h"
#include "Shape.h"
#include "..\Texture.h"
#include "..\AI\PathPlanning.h"
#include "..\AI\aStarSearch.h"
#include "..\GUI\Health.h"

enum ObjectType
{
	PROJECTILE,
	ENEMY,
	OTHER
};

class GameObject
{
public:
	GameObject(ObjectType type, Vector2D position, const char* texPath, Vector2D *vects, SDL_Renderer* renderer);
	GameObject(ObjectType type, Vector2D position, const char* texPath, Vector2D *vects, std::vector<Node*> nodePath, SDL_Renderer* renderer, Health* health);
	~GameObject();

	bool Initialise();
	void Update(float delta);
	void Render(bool debug);
	void Destroy();
	static void SquareCollides(GameObject* obj, GameObject* objTwo);
	static bool Collided(GameObject* obj, GameObject* objTwo, Vector2D axis);

	RigidBody			_rigidBody;
	Shape				_shape;
	ObjectType			_type;
	bool				_deleted = false;
	PathPlanning*		_plan;

private:
	SDL_Renderer*		_renderer; 
	Texture*			_texture;
	Health*				_health;

	Vector2D			_screenMin = Vector2D(0, 1080);
	Vector2D			_screenMax = Vector2D(1920, 0);
};

#endif