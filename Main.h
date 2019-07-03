#pragma once
#include "Texture.h"
#include "maths/Timer.h"
#include "maths/Vector2D.h"
#include "Level/Floor.h"
#include "Level/Spawner.h"
#include "Level/MapGrid.h"
#include "GUI/Health.h"
#include "GUI/Ability.h"

#include "Physics/GameObject.h"
#include "ObjectList.h"

void Destroy();
bool Initialise();
void LoadTextures();
void DrawGrid();
void SetupPathfinding();
void CheckControls();


const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS = 1000 / SCREEN_FPS;
const int PHYSICS_FPS = 60;
const int PHYSICS_TICKS = 1000 / PHYSICS_FPS;

float oldPhysicsTime = 0;
float oldScreenTime = 0; 
int countedFrames = 0;
bool quit;
SDL_Event e;

Vector2D enemySizeVerts[] = {
		Vector2D(-10, -10), Vector2D(10, -10),
		Vector2D(10,  10), Vector2D(-10,  10)
};

SDL_Window* window = NULL;
SDL_Renderer* renderer;
ObjectList* objList = new ObjectList(); 

Timer fpsTime;
Timer screenTimer;
Timer physicsTimer;

Spawner enemySpawner = Spawner();

float delta;

GameObject* box;
GameObject* boxTwo;

Floor* levelFloor; 

float playerSpeed = 5.0f;

Texture* wood;
Texture* leaf;
Texture* background;
Texture* apple;
Texture* deathscreen;

Node* goal;
Node* spawn;

Health* health;
Ability* ability;

bool	_debug = false; 