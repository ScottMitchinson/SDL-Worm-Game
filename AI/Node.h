#pragma once
#include "..\maths\Vector2D.h"
#include <math.h>

class Node
{
public:
	Node(float x, float y);
	Node();
	~Node();
	void SetNodeLocation(float x, float y);

	float GetX();
	float GetY();
	void SetX(float x);
	void SetY(float y);
	int GetFCost();

	int _hCost;
	int _gCost;
	Node* _parent;
	bool _walkable;


private:
	Vector2D _location;

};

