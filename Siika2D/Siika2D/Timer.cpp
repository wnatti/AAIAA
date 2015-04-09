#include "Timer.h"

using namespace misc;

Timer::Timer()
{
}


Timer::~Timer()
{
}

void Timer::reset()
{
	auto start = std::chrono::high_resolution_clock::now();
}

float Timer::getElapsedTime()
{
	float elapsed = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::duration<float, std::<milli>>>
		(clock.now() - start).count();
}

