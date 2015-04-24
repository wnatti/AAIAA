#pragma once
#include "Sound.h"
#include <vector>
namespace audio
{
	class Effect : public Sound
	{
	public:
		Effect(std::vector<unsigned char>* soundData) :Sound(soundData)
		{
		};
		~Effect(){};
	private:

	};
}