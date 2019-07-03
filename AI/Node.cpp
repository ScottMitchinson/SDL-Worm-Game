#include "Node.h"

Node::Node(float x, float y)
{
	_location = Vector2D(x, y);
}

Node::Node()
{
	_location = Vector2D(0, 0);
}


Node::~Node()
{
}

int Node::GetFCost()
{
	return _gCost + _hCost;
}

void Node::SetNodeLocation(float x, float y)
{
	_location.SetX(x);
	_location.SetY(y);
}

float Node::GetX()
{
	return _location.GetX();
}

float Node::GetY()
{
	return _location.GetY();
}

void Node::SetX(float x)
{
	_location.SetX(x);
}

void Node::SetY(float y)
{
	_location.SetY(y);
}