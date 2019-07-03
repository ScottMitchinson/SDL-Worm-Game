#pragma once
#include <math.h>

class Vector2D
{
public:
	Vector2D();
	~Vector2D();
	float GetX();
	float GetY();
	void SetX(float x);
	void SetY(float y);
	Vector2D(float x, float y);
	Vector2D& operator= (const Vector2D &vect);
	Vector2D& operator+ (const Vector2D &vect);
	Vector2D& operator- (const Vector2D &vect);
	Vector2D& operator* (const Vector2D &vect);
	
	static float Dot(Vector2D one, Vector2D two);

private:
	float _x;
	float _y;
};

