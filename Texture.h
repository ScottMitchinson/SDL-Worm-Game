#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class Texture
{
public:
	Texture(SDL_Renderer* renderer);
	~Texture();
	int getWidth();
	void Destroy();
	int getHeight(); 
	void Render(int xPos, int yPos, int xSize, int ySize);
	bool LoadFromFile(const char* path);

private:
	SDL_Texture* _texture; 
	SDL_Renderer* _renderer; 
	int _height;
	int _width;
};



