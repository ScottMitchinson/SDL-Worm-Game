#pragma once
#ifndef ASTARSEARCH_H
#define ASTARSEARCH_H

#include "Node.h"
#include "..\maths\Vector2D.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <list>

std::vector<Node*> ReturnPath();
std::vector<Node*> FindPath(Node* start, Node* end);
std::list<Node*> GetSurroundingNodes(Node* no);
void FillGrid();
int CalculateDistance(Node* start, Node* end);
void CreatePath(Node* start, Node* end, std::list<Node*> list);

#endif