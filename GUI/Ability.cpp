#include "Ability.h"



Ability::Ability(SDL_Renderer* render)
{
	_uses = 3;
	_wind = new Texture(render);
	_wind->LoadFromFile("res\\GUI\\Wind.png");
}

Ability::~Ability()
{
}

//Renders the ability icons in the corner of the screen
void Ability::Render()
{
	for (int i = 0; i < _uses; i++)
	{
		_wind->Render((100 * i) + 50, 140, 100, 100);
	}
}

//uses an ability and decreases the number left
void Ability::Use()
{
	_uses--;
	if (_uses < 0)
	{
		_uses = 0;
	}
}

//Returns true if there are any uses of the ability left
bool Ability::Available()
{
	if (_uses > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}