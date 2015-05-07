#pragma once

#include "AudioInitializer.h"
#include "AudioPlayer.h"
#include <string>
#include <vector>

namespace audio
{
	class Audio
	{
	public:
		
		Audio(std::string fileName, core::ResourceManager* resourceManager);
		Audio(){};
		~Audio();

		/**
		* Starts a player.
		* Returns false if there are no available audio players.
		*/
		bool Play();
		/**
		* Stops all the instances of this Audio object.
		* Next time playing will start from the beginning.
		*/
		void Stop();
		/**
		* Pauses all the players of this Audio object.
		* Next time playing will continue from the same point.
		*/
		void Pause();
		
		/**
		* Sets the volume to given value.
		* Give volumeLevel as percentage.
		*/
		void SetVolume(float volumeLevel);
		/**
		* Sets looping to given value.
		* 'isEnabled = true' enables looping.
		* 'isEnabled = false' disables looping.
		*/
		void SetLooping(bool isEnabled);

		/**
		/* MaxPlayerCount default = 3
		* MaxPlayerCount defines how many instances of this Audio object
		* can be played at once. 
		*/
		void SetMaxPlayerCount(unsigned newMaxCount);
		
	private:

		AudioPlayer* GetAvailable();

		std::vector<AudioPlayer*> player;

		unsigned playerCount;
		unsigned maxPlayerCount;
	};
}