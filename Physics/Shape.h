#pragma once
#include <vector>
#include "SDL.h"
#include "..\maths\Vector2D.h"

typedef struct MinMax {
	float min;
	float max;
} MinMax;

class Shape
{
public:
	Shape(); 
	Shape(Vector2D* vects);
	~Shape();
	void CreateShape(Vector2D *vects);
	Vector2D GetMin(Vector2D center);
	Vector2D GetMax(Vector2D center);
	void SetCollided(bool collided);
	void Render(Vector2D position, SDL_Renderer* render, bool collided, bool debug);
	MinMax GetInterval(Vector2D axis, Vector2D pos);
	float						_bounce = 0.8f;
	bool						_collided; 

private:
	std::vector<Vector2D>		_shapeVertices;
	Vector2D					_shapeMin;
	Vector2D					_shapeMax;
};

