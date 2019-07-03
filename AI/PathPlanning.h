#pragma once
#include <vector>
#include "Node.h"
#include <math.h>

class PathPlanning
{
public:
	PathPlanning();
	PathPlanning(std::vector<Node*> ReturnPath);
	~PathPlanning();
	void SetPath(std::vector<Node*> ReturnPath);
	std::vector<Vector2D> TranslatePath(std::vector<Node*> ReturnPath);
	Vector2D GetStartPosition();
	Vector2D FollowPath(Vector2D currentPos);
	int distance(Vector2D a, Vector2D b);

private:
	std::vector<Vector2D>	_newPath;
	int						_nodeNum;
};

