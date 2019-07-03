#pragma once
#include <stdlib.h>

class Spawner
{
public:
	bool SpawnEnemy();
	void IncreaseTime();


private:
	const int		_sleepTime = 40;
	int				_count = 0;
};

