#include "ObjectList.h"


ObjectList::ObjectList()
{
}

ObjectList::~ObjectList()
{
}

bool ObjectList::Initialise()
{
	return true;
}

void ObjectList::Update(float delta)
{
	CullList();
	for (GameObject* obj : _objects)
	{
		obj->Update(delta);
	}
	CheckCollisions();
}

//Removes any objects that have been set to be deleted by other methods
void ObjectList::CullList()
{
	std::vector<GameObject*> newList;
	for (GameObject* obj : _objects)
	{
		if (obj->_deleted == false)
		{
			newList.push_back(obj);
		}
	}
	_objects = newList;
}

void ObjectList::Render(bool debug)
{
	for (GameObject* obj : _objects)
	{
		obj->Render(debug); 
	}
}

void ObjectList::Destroy()
{
	for (GameObject* obj : _objects)
	{
		obj->Destroy();
	}
}

void ObjectList::Add(GameObject* object)
{
	_objects.push_back(object);
}

//Removes an item specified by type
bool ObjectList::RemoveItem(ObjectType type)
{
	int count = 0;
	bool found = false;
	for (GameObject* obj : _objects)
	{
		if (obj->_type == type)
		{
			obj->_deleted = true;
		}
		count++;
	}

	return true;
}

//Does a search to check collisions
//Has been wrote so shapes wont be tested against eachother more than once, saving time
void ObjectList::CheckCollisions()
{
	for (int i = 0; i < _objects.size(); i++)
	{
		for (int i2 = i + 1; i2 < _objects.size(); i2++)
		{
			GameObject::SquareCollides(_objects[i2], _objects[i]);
		}
	}
}

//When the Wind ability has been used this will apply a force to all enemies on the map
void ObjectList::AbilityUsed()
{
	for (GameObject* obj : _objects)
	{
		if (obj->_type == ENEMY)
		{
			obj->_shape._collided = true;
			obj->_rigidBody.SetGravityEffected(true);
			obj->_rigidBody.ApplyForce(Vector2D(-20.0f, 0));
		}
	}
}