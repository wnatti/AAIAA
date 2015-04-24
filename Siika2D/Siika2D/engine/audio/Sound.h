#pragma once
#include <vector>
#include "../misc/Timer.h"

//#include "Audio.h"
namespace audio
{
	class Sound
	{
	public:
		friend class Audio;
		Sound(std::vector<unsigned char>* soundData, unsigned long clipLength = 5000)
		{
			_clipLength = clipLength;
			unsigned long size = soundData->size() * sizeof(unsigned char);
			clip_buffer = (void*)soundData->data();
			clip_size = size;// soundData->size() * sizeof(unsigned char);
			_isPlaying = false;
			_isDone = false;
		};

		~Sound(){};
		bool update()
		{
			if(!_isPlaying)
				return false;

			//TODO: needs to check clip length
			//long length = clip_size / clip_samples_per_sec;

			if(timer.getElapsedTime(TIME::MILLISECONDS) > _clipLength)
			{
				_isDone = true;
				return _isDone;
			}
			return false;
		}
		void play(void){};
		bool operator==(const Sound rhs)
		{	
			//Same clip at same position is Id of some kind needed?
			if(this->clip_buffer == rhs.clip_buffer && this->timer == rhs.timer)
			{
				return true;

			}
		}
		
	private:
		//Audio *_ad;
		unsigned long _clipLength;
		misc::Timer timer;
		const void *clip_samples;             //the raw samples
		unsigned int clip_num_samples;        //how many samples there are
		unsigned int clip_samples_per_sec;    //the sample rate in Hz
		void * clip_buffer;
		SLuint32 clip_size;
		bool _isPlaying, _isDone;
	};
}
/*
void Sound::play(void)
{
	
	(*_ad->player_buf_q)->Enqueue(_ad->player_buf_q, clip_buffer, clip_size);
	_ad->_isPlaying = true;
	_ad->_isDone = false;

	(*_ad->player)->SetPlayState(_ad->player, SL_PLAYSTATE_PLAYING);
	
	//play_start_time = current_time();

}
*/