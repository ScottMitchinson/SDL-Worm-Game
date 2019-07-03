#pragma once
#ifndef OBJECTLIST_H
#define OBJECTLIST_H
#include "Physics/GameObject.h"
#include <vector>

class ObjectList
{
public:
	ObjectList();
	~ObjectList();

	bool Initialise();
	void Update(float delta);
	void Render(bool debug);
	void Destroy();

	void Add(GameObject* object);
	bool RemoveItem(ObjectType type);
	void CullList();
	void CheckCollisions();
	void AbilityUsed();

	std::vector<GameObject*>		_objects;

private:
};

#endif