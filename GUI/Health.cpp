#include "Health.h"

Health::Health(SDL_Renderer* render)
{
	_hit = false;
	_health = 3;
	_heart = new Texture(render);
	_heart->LoadFromFile("res\\GUI\\Heart.png");	
}

//Renders the hearts in the top corner of the screen
void Health::Render()
{
	for (int i = 0; i < _health; i++)
	{
		_heart->Render((100 * i) + 50, 50, 100, 100);
	}
}

void Health::Hit()
{
	_health--;
	_hit = true;
	if (_health == 0)
	{
		_dead = true;
	}
}

Health::~Health()
{
}


