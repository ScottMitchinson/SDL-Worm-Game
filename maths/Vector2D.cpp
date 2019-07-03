#include "Vector2D.h"

Vector2D::Vector2D()
{
	_x = 0;
	_y = 0;
}

Vector2D::Vector2D(float x, float y)
{
	_x = x;
	_y = y;
}

Vector2D::~Vector2D()
{
}

float Vector2D::GetX()
{
	return _x;
}

float Vector2D::GetY()
{
	return _y;
}

void Vector2D::SetX(float x)
{
	_x = x;
}

void Vector2D::SetY(float y)
{
	_y = y;
}

Vector2D& Vector2D::operator= (const Vector2D &vect)
{
	_x = vect._x;
	_y = vect._y;
	return *this;
}

Vector2D& Vector2D::operator+ (const Vector2D &vect)
{
	_x += vect._x;
	_y += vect._y;
	return *this;

}

Vector2D& Vector2D::operator- (const Vector2D &vect)
{
	_x -= vect._x;
	_y -= vect._y;
	return *this;
}

Vector2D& Vector2D::operator* (const Vector2D &vect)
{
	_x *= vect._x;
	_y *= vect._y;
	return *this;
}


float Vector2D::Dot(Vector2D one, Vector2D two)
{
	float result = (one.GetX() * two.GetX()) + (one.GetY() * two.GetY());
	return result;
}