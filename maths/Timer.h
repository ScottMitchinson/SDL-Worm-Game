#pragma once
#include "SDL.h"

class Timer
{
public:

	Timer();
	void start();
	Uint32 getTicks();

private:
	Uint32		_startTicks;
	Uint32		_pausedTicks;
	bool		_paused;
	bool		_started;
};

