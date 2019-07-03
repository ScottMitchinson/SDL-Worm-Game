#pragma once
#include "..\Texture.h"

class Health
{
public:
	Health(SDL_Renderer* render);
	void Hit();
	~Health();
	void Render();

	int				_health;
	bool			_hit;
	bool			_dead;

private:
	Texture*		_heart;
	Texture*		_hitTex;
};

