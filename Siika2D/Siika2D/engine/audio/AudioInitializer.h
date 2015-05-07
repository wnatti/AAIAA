#pragma once

#include "AudioPlayer.h"

namespace audio
{
	class AudioInitializer
	{
	public:
		static AudioInitializer* GetInstance();

		void InitAudioPlayer(AudioPlayer* player);
		
	private:
		void CreateEngine();

		AudioInitializer();
		~AudioInitializer();		

		SLresult result;

		SLObjectItf engineObj;
		SLEngineItf engine;

		SLObjectItf outputMixObj;
		SLVolumeItf outputMixVol;

		static AudioInitializer* instance;
	};
}