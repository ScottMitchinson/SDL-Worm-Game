#include "Timer.h"

Timer::Timer()
{
	_startTicks = 0;
	_pausedTicks = 0;
	_paused = false;
	_started = false;
}

void Timer::start()
{
	_started = true;
	_paused = false;
	_startTicks = SDL_GetTicks();
	_pausedTicks = 0;
}

//Returns how many ticks have passed since the program started
Uint32 Timer::getTicks()
{
	Uint32 time = 0;
	if (_started)
	{
		if (_paused)
		{
			time = _pausedTicks;
		}
		else
		{
			time = SDL_GetTicks() - _startTicks;
		}
	}

	return time;
}