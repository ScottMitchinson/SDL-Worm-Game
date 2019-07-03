#pragma once
#include "..\Physics\GameObject.h"
#include "..\ObjectList.h"

class Floor
{
public:
	Floor(unsigned int height, const char* texture, SDL_Renderer* renderer);
	~Floor();
	void Render(bool debug);
	void SquareCollides(ObjectList* list);
	bool Collided(GameObject* obj);

	Shape*			_floor; 
	Vector2D		_centre;

private:
	SDL_Renderer*	_renderer;
	Texture*		_texture;
	Vector2D		_texPrintLocation;
	float			_bounce = 0.2f;
	float			_friction = 0.5f;
};

