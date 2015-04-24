#pragma once
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include "Sound.h"
#include "Track.h"
#include "Effect.h"
#include <vector>
#include <list>

// http://vec3.ca/getting-started-with-opensl-on-android/
// https://audioprograming.wordpress.com/2012/03/03/android-audio-streaming-with-opensl-es-and-the-ndk/
namespace audio
{
	class Audio
	{
		friend class Sound;
	public:
		Audio();
		~Audio(){};
		void createPlayer(void);
		bool checkPlaying(void);
		void SLAPIENTRY play_callback(SLPlayItf player, void *context, SLuint32 event)
		{
			if(event & SL_PLAYEVENT_HEADATEND)
				_curPlaying->_isDone = true;
			//_isDone = true;
		}
		Effect * createEffect(std::vector<unsigned char> * soundData);
		//TODO: needs to create its own buffer to track data
		Track *  createTrack(std::vector<unsigned char> * soundData);
		bool playSound(Sound * toPlay);
		void update(void)
		{
			//TODO: Needs to go through _sounds to see if anything is still playing
			if(_isDone == true && _isPlaying == true)
			{
				(*player_buf_q)->Clear(player_buf_q);
				_isPlaying = false;
			}
		};
	private:

		SLObjectItf _engine_obj;
		SLEngineItf _engine;
		SLObjectItf _output_mix_obj;
		SLVolumeItf _output_mix_vol;

		SLAndroidSimpleBufferQueueItf player_buf_q;
		SLObjectItf player_obj;
		SLPlayItf player;
		SLVolumeItf player_vol;
		std::vector<Sound *> _sounds;
		std::list<Sound> _playingSounds;
		Sound * _curPlaying;

		bool _isPlaying, _isDone;
	};
}