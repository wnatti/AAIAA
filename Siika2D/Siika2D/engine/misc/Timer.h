#pragma once
#include <ctime>
enum TIME
{SECONDS, MILLISECONDS, MICROSECONDS};

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
		double getElapsedTime(TIME time);

	private:
		std::clock_t _start;
	};
}
