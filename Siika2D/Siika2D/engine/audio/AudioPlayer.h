#pragma once

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <string>
#include "../core/ResourceManager.h"

namespace audio
{ 
	class AudioPlayer 
	{
		friend class AudioInitializer;

	public:
		AudioPlayer(core::Audio* audioAsset){ _audioAsset = audioAsset; }
		AudioPlayer(AudioPlayer* pointer);
		~AudioPlayer();

		/**
		* 1 = SL_PLAYSTATE_STOPPED
		* 2 = SL_PLAYSTATE_PAUSED
		* 3 = SL_PLAYSTATE_PLAYING
		*/
		SLuint32 GetPlayState();

		void SetPlayState(SLuint32 state);
		void SetLooping(bool isEnabled); 
		void SetVolume(float volPercentage);
		core::Audio* getAudioAsset(){ return _audioAsset; }

	private:
		void CheckError();

		SLObjectItf audioPlayerObj;
		SLPlayItf audioPlayerPlay;
		SLSeekItf audioPlayerSeek;
		SLVolumeItf audioPlayerVol;

		SLresult result;

		core::Audio* _audioAsset;

		int fileDescriptor;
		off_t start, length;
	};
}