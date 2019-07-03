#pragma once
#include "..\Texture.h"

class Ability
{
public:
	Ability(SDL_Renderer* render);
	~Ability();
	void Render();
	void Use();
	bool Available();
	int			_uses;

private:
	Texture*	_wind; 
};