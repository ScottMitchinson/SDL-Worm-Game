#include "Texture.h"

Texture::Texture(SDL_Renderer* renderer)
{
	_texture = NULL;
	_renderer = renderer;
	_width = 0;
	_height = 0;
}

Texture::~Texture()
{
	Destroy(); 
}

//Loads the Texture at the selected Path, also sets the height and width values that can be used later by other methods
bool Texture::LoadFromFile(const char* path)
{
	Destroy(); 
	bool succ = true;
	SDL_Surface* loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
	{
		succ = false;
	}
	_texture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
	if (_texture == NULL)
	{
		succ = false;
	}
	SDL_FreeSurface(loadedSurface);
	SDL_QueryTexture(_texture, NULL, NULL, &_width, &_height);
	return succ;
}

void Texture::Render(int xPos, int yPos, int xSize, int ySize)
{
	SDL_Rect rect = { xPos - (xSize / 2), yPos - (ySize / 2), xSize, ySize };
	SDL_RenderCopy(_renderer, _texture, NULL, &rect);
}

void Texture::Destroy()
{
	SDL_DestroyTexture(_texture);
	_texture = NULL; 
}

int Texture::getHeight()
{
	return _height;
}

int Texture::getWidth()
{
	return _width;
}