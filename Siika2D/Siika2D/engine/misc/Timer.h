#pragma once
#include <chrono>
#include <ctime>

namespace misc
{
	class Timer
	{
	public:
		Timer(std::clock_t start);
		~Timer();
		/**
		Function for reseting the start time
		*/
		void reset();
		/**
		Gets time in seconds
		*/
		double getElapsedTime();

	private:
		std::clock_t _start;
	};
}
