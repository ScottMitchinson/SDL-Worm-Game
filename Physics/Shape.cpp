#include "Shape.h"

//This class has been wrote to support complex polygons, however the SAT methods have been wrote to support squares so calls to this method just use squares

Shape::Shape()
{
	//Creates a 3x3 Box if the Vectors are not passed in
	_collided = false; 
	Vector2D verts[] = {
		Vector2D(-1, -1), Vector2D(1, -1),
		Vector2D(1,  1), Vector2D(-1,  1)
	};
	CreateShape(verts);
}

Shape::Shape(Vector2D* vects)
{
	CreateShape(vects); 
	_collided = false; 
}


Shape::~Shape()
{
}

//Renders the shape with lines if the debug mode is on, if not it just skips this
void Shape::Render(Vector2D position, SDL_Renderer* render, bool collided, bool debug)
{
	if (debug)
	{
		if (_collided)
		{
			SDL_SetRenderDrawColor(render, 255, 0, 0, SDL_ALPHA_OPAQUE);
		}
		else
		{
			SDL_SetRenderDrawColor(render, 0, 255, 0, SDL_ALPHA_OPAQUE);
		}

		int count = 0;
		for (count = 0; count < _shapeVertices.size() - 1; count++)
		{
			SDL_RenderDrawLine(render, position.GetX() + _shapeVertices[count].GetX(),
								position.GetY() + _shapeVertices[count].GetY(),
								position.GetX() + _shapeVertices[count + 1].GetX(),
								position.GetY() + _shapeVertices[count + 1].GetY());
		}
		SDL_RenderDrawLine(render, position.GetX() + _shapeVertices[count].GetX(),
							position.GetY() + _shapeVertices[count].GetY(),
							position.GetX() + _shapeVertices[0].GetX(),
							position.GetY() + _shapeVertices[0].GetY());
	}


}

//Creates the distance covered by the axis, if the axis is (0, 1) then the min max is generated for the Y axis 
MinMax Shape::GetInterval(Vector2D axis, Vector2D pos)
{
	MinMax result;
	result.max = 10;
	result.min = 20;

	Vector2D min = _shapeMin;
	Vector2D max = _shapeMax;

	Vector2D verts[] = {
		Vector2D(min.GetX() + pos.GetX(), min.GetY() + pos.GetY()), Vector2D(min.GetX() + pos.GetX(), max.GetY() + pos.GetY()),
		Vector2D(max.GetX() + pos.GetX(), max.GetY() + pos.GetY()), Vector2D(max.GetX() + pos.GetX(), min.GetY() + pos.GetY())
	};

	result.min = result.max = (Vector2D::Dot(axis, verts[0]));
	for (int i = 1; i < 4; ++i)
	{
		float projection = Vector2D::Dot(axis, verts[i]);
		if (projection < result.min)
		{
			result.min = projection;
		}
		if (projection > result.max)
		{
			result.max = projection;
		}
	}
	return result;
}

//Fills the list with vectors of positions on the shape
void Shape::CreateShape(Vector2D* vects)
{
	for (int i = 0; i < 4; i++)
	{
		_shapeVertices.push_back(vects[i]);
	}

	_shapeMin = Vector2D(_shapeVertices[1].GetX(), _shapeVertices[1].GetY());
	_shapeMax = Vector2D(_shapeVertices[3].GetX(), _shapeVertices[3].GetY());
}

Vector2D Shape::GetMin(Vector2D center) 
{
	return _shapeMin + center; 
}

Vector2D Shape::GetMax(Vector2D center)
{
	return _shapeMax + center;
}

void Shape::SetCollided(bool collided)
{
	_collided = collided;
}

