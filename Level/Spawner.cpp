#include "Spawner.h"

//will randomy generate a number that determines if an enemy is spawned or not
//Will stop working for 40 ticks before working again
bool Spawner::SpawnEnemy()
{
	IncreaseTime();
	if (_count > _sleepTime)
	{
		int spawnChance = rand() % 100 + 1;
		if (spawnChance > 97)
		{
			_count = 0;
			return true;
		}
	}
	return false;
}

void Spawner::IncreaseTime()
{
	_count++;
}