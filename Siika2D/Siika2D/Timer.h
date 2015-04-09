#pragma once
#include <chrono>
#include <ctime>

namespace misc
{
	class Timer
	{
	public:
		Timer();
		~Timer();
		void reset();
		float getElapsedTime();

	private:
		double _start;
	};
}
