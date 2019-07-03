#include "PathPlanning.h"

PathPlanning::PathPlanning()
{

}

void PathPlanning::SetPath(std::vector<Node*> ReturnPath)
{
	_newPath = TranslatePath(ReturnPath);
	_nodeNum = _newPath.size() - 1;
}

PathPlanning::PathPlanning(std::vector<Node*> ReturnPath)
{
	_newPath = TranslatePath(ReturnPath);
	_nodeNum = _newPath.size() - 1; 
}

Vector2D PathPlanning::GetStartPosition()
{
	return _newPath[_nodeNum];
}

PathPlanning::~PathPlanning()
{
}

//Due the the array for pathfinding using values 1 to 40, this method changes the node list into values more screen sized, and in the correct place for the tree to be rendered
std::vector<Vector2D> PathPlanning::TranslatePath(std::vector<Node*> ReturnPath)
{
	std::vector<Vector2D> path;
	for (Node* node : ReturnPath)
	{
		Vector2D vect = Vector2D((node->GetX() * 24) + 972, (node->GetY() * 24) + 12);
		path.push_back(vect);
	}
	return path;
}



//Checks the position towards the next node, if it is not the next node it works out a velocity towards the next node
Vector2D PathPlanning::FollowPath(Vector2D currentPos)
{
	if (currentPos.GetX() == _newPath[_nodeNum].GetX() && currentPos.GetY() == _newPath[_nodeNum].GetY())
	{
		_nodeNum--;
		if (_nodeNum < 0)
		{
			_nodeNum = 0;
		}
	}

	if (currentPos.GetX() != _newPath[_nodeNum].GetX())
	{
		if (currentPos.GetX() > _newPath[_nodeNum].GetX())
		{
			return Vector2D(-2, 0);
		}
		else if (currentPos.GetX() < _newPath[_nodeNum].GetX())
		{
			return Vector2D(2, 0);
		}
	}
	else if (currentPos.GetY() != _newPath[_nodeNum].GetY())
	{
		if (currentPos.GetY() > _newPath[_nodeNum].GetY())
		{
			return Vector2D(0, -2);
		}
		else if (currentPos.GetY() < _newPath[_nodeNum].GetY())
		{
			return Vector2D(0, 2);
		}
	}

	return Vector2D(0, 0);
}

int PathPlanning::distance(Vector2D a, Vector2D b)
{
	return sqrt((a.GetX() - b.GetX()) * (a.GetX() - b.GetX()) + (a.GetY() - b.GetY()) * (a.GetY() - b.GetY()));
}