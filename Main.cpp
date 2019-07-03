#include "SDL.h"
#include "Main.h"
#include <iostream>

bool Initialise()
{
	SDL_Init(SDL_INIT_VIDEO);
	quit = false;	
	
	fpsTime.start();
	
	window = SDL_CreateWindow("Game Behavior Project",
								SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED,
								SCREEN_WIDTH,
								SCREEN_HEIGHT,
								SDL_WINDOW_SHOWN);
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
	{
		std::cout << "Error setting Up Renderer" << std::endl;
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	levelFloor = new Floor(100, "res\\Textures\\FloorCanasStone.png", renderer);
	
	health = new Health(renderer);
	ability = new Ability(renderer);

	LoadTextures();
	SetupPathfinding();
	FillGrid();
	FindPath(spawn, goal);

	return true;
}

void LoadTextures()
{
	deathscreen = new Texture(renderer);
	deathscreen->LoadFromFile("res\\DeathScreen.png");

	wood = new Texture(renderer);
	wood->LoadFromFile("res\\Tree\\Wood.png");

	leaf = new Texture(renderer);
	leaf->LoadFromFile("res\\Tree\\LeafTwo.png");

	background = new Texture(renderer);
	background->LoadFromFile("res\\Background.png");

	apple = new Texture(renderer);
	apple->LoadFromFile("res\\Tree\\Apple.png");
}

void SetupPathfinding()
{
	goal = new Node();
	spawn = new Node();

	goal->SetNodeLocation(5, 12);
	spawn->SetNodeLocation(35, 35);
}

void Destroy()
{
	leaf->Destroy();
	wood->Destroy();
	background->Destroy();
	deathscreen->Destroy();
	apple->Destroy();

	objList->Destroy();

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}

int main(int argc, char* args[])
{
	if (!Initialise())
	{
		Destroy();
		return 0;
	}
	
	while (!quit)
	{
		screenTimer.start();
			
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			CheckControls();
		}

		float avgFPS = countedFrames / (fpsTime.getTicks() / 1000.f);
		if (avgFPS > 2000000)
		{
			avgFPS = 0;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		++countedFrames;

		float ticks = SDL_GetTicks(); 
		float functionDelta = (delta - ticks) / 1000; 

#pragma region UPDATE
			
		int frameTicks = screenTimer.getTicks();
		if (!health->_dead)
		{
			if (enemySpawner.SpawnEnemy() == true)
			{
				GameObject* object = new GameObject(ENEMY, Vector2D(1880, 950), "res\\Enemy\\Worm.png", enemySizeVerts, ReturnPath(), renderer, health);
				object->_rigidBody.SetGravityEffected(false);
				objList->Add(object);
			}

			//Update the physics
			if (oldPhysicsTime < SDL_GetTicks() / PHYSICS_TICKS)
			{
				oldPhysicsTime = SDL_GetTicks() / PHYSICS_TICKS;
				levelFloor->SquareCollides(objList);
				objList->Update(functionDelta); 
			}
		}
		else
		{
			//When the player is dead, remove all the enemies
			objList->RemoveItem(ENEMY);
		}

			

#pragma endregion
			
		delta = ticks;

#pragma region RENDER
			
		if (health->_dead)
		{
			deathscreen->Render(960, 540, 1920, 1080);
		}
		else
		{
			background->Render(960, 540, 1920, 1080);

			//Creates the line used for aiming
			int x, y;
			SDL_GetMouseState(&x, &y);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawLine(renderer, 100, 900, x, y);

			DrawGrid();
			levelFloor->Render(_debug);
			objList->Render(_debug); 

			apple->Render(1092, 300, 30, 30);

			health->Render();
			ability->Render();
		}
			


#pragma endregion

		//update the display
		SDL_RenderPresent(renderer);

		//Delay to 60 Frames 
		if (frameTicks < SCREEN_TICKS)
		{
			SDL_Delay(SCREEN_TICKS - frameTicks);
		}
	}
	
	Destroy();
	return 0;
}

void CheckControls()
{
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
	{
		quit = true;
	}

	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_d && health->_dead == false)
	{
		if (_debug == true)
		{
			_debug = false;
		}
		else
		{
			_debug = true;
		}
	}

	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE && health->_dead == true)
	{
		ability->_uses = 3;
		health->_health = 3;
		health->_dead = false;
	}

	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && health->_dead == false)
	{
		objList->RemoveItem(PROJECTILE);

		int x, y;
		SDL_GetMouseState(&x, &y);

		Vector2D texSizeVerts[] = {
			Vector2D(-20, -20), Vector2D(20, -20),
			Vector2D(20,  20), Vector2D(-20,  20)
		};

		GameObject* object = new GameObject(PROJECTILE, Vector2D(100, 900), "res\\Textures\\Melon.png", texSizeVerts, renderer);
		y = (900 - y) / 10;
		y = -y;
		x = (x - 100) / 10;
		if (x > 20)
		{
			x = 20;
		}

		if (y < -20)
		{
			y = -20;
		}


		object->_rigidBody.ApplyForce(Vector2D(x, y));
		objList->Add(object);
	}

	//Uses the Wind ability which adds a force to all enemies on the screen
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT && health->_dead == false)
	{
		if (ability->Available() == true)
		{
			ability->Use();
			objList->AbilityUsed();
		}
	}

	//
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_a && _debug == true)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		GameObject* object = new GameObject(OTHER, Vector2D(x, y), "res\\Enemy\\Worm.png", enemySizeVerts, renderer);
		object->_rigidBody.SetGravityEffected(true);
		objList->Add(object);
	}
}

void DrawGrid()
{
	for (int y = 0; y < 40; y++)
	{
		for (int x = 0; x < 40; x++)
		{
			if (TextureGrid[y][x] == 0)
			{
				wood->Render(((x * 24) + 12) + 960, (y * 24) + 12, 35, 35);
			}
		}

	}

	for (int y = 0; y < 40; y++)
	{
		for (int x = 0; x < 40; x++)
		{
			if (TextureGrid[y][x] == 2)
			{
				leaf->Render(((x * 24) + 12) + 960, (y * 24) + 12, 35, 35);
			}
		}

	}

	if (_debug == true)
	{
		std::vector<Node*> nodePath = ReturnPath();

		for (int i = 1; i <= nodePath.size() - 1; i++)
		{
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawLine(renderer, (nodePath[i - 1]->GetX() * 24) + 972,
				(nodePath[i - 1]->GetY() * 24) + 12,
				(nodePath[i]->GetX() * 24) + 972,
				(nodePath[i]->GetY() * 24) + 12);

		}
	}
}

