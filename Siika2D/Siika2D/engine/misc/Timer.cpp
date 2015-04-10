#include "Timer.h"

using namespace misc;

Timer::Timer(std::clock_t start)
{
	start = _start;
}


Timer::~Timer()
{
}

void Timer::reset()
{
	std::clock_t _start;
}

double Timer::getElapsedTime()
{
	double elapsed;
	elapsed = (std::clock() - _start) / (double)CLOCKS_PER_SEC;
	return elapsed;
}

