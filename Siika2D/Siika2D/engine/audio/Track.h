#pragma once
#include "Sound.h"
namespace audio
{
	class Track : public Sound
	{
	public:
		Track(std::vector<unsigned char>* soundData) :Sound(soundData){};
		~Track(){};

	private:

	};
}