#include "Audio.h"
namespace audio
{
	Audio::Audio()
	{


		SLresult result;
		result = slCreateEngine(&_engine_obj, 0, nullptr, 0, nullptr, nullptr);
		(*_engine_obj)->Realize(_engine_obj, SL_BOOLEAN_FALSE);
		(*_engine_obj)->GetInterface(_engine_obj, SL_IID_ENGINE, &_engine);


		const SLInterfaceID ids[] = { SL_IID_VOLUME };
		const SLboolean req[] = { SL_BOOLEAN_FALSE };

		(*_engine)->CreateOutputMix(_engine, &_output_mix_obj, 1, ids, req);

		(*_output_mix_obj)->Realize(_output_mix_obj, SL_BOOLEAN_FALSE);

		if((*_output_mix_obj)->GetInterface(_output_mix_obj,
			SL_IID_VOLUME, &_output_mix_vol) != SL_RESULT_SUCCESS)
			_output_mix_vol = nullptr;

	}
	void Audio::createPlayer(void)
	{
		SLuint32 clip_samples_per_sec = 441000;
		//Creating audio buffer -> to Audio ?
		SLDataLocator_AndroidSimpleBufferQueue in_loc;
		in_loc.locatorType = SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE;
		in_loc.numBuffers = 1;


		//Setting format
		SLDataFormat_PCM format;
		format.formatType = SL_DATAFORMAT_PCM;
		format.numChannels = 1;
		format.samplesPerSec = 22000;//clip_samples_per_sec * 1000; //mHz
		format.bitsPerSample = SL_PCMSAMPLEFORMAT_FIXED_16;
		format.containerSize = 16;
		format.channelMask = SL_SPEAKER_FRONT_CENTER;
		format.endianness = SL_BYTEORDER_LITTLEENDIAN;

		SLDataSource src;
		src.pLocator = &in_loc;
		src.pFormat = &format;

		SLDataLocator_OutputMix out_loc;
		out_loc.locatorType = SL_DATALOCATOR_OUTPUTMIX;
		out_loc.outputMix = _output_mix_obj;

		SLDataSink dst;
		dst.pLocator = &out_loc;
		dst.pFormat = nullptr;

		//##



		//create the object
		SLresult res;
		const SLInterfaceID ids[] = { SL_IID_VOLUME, SL_IID_ANDROIDSIMPLEBUFFERQUEUE };
		SLuint32 idsCount = sizeof(ids) / sizeof((ids[0]));
		const SLboolean req[] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };

		res = (*_engine)->CreateAudioPlayer(_engine, &player_obj, &src, &dst, idsCount, ids, req);
		(*player_obj)->Realize(player_obj, SL_BOOLEAN_FALSE);

		(*player_obj)->GetInterface(player_obj, SL_IID_PLAY, &player);
		(*player_obj)->GetInterface(player_obj, SL_IID_VOLUME, &player_vol);

		(*player_obj)->GetInterface(player_obj, SL_IID_ANDROIDSIMPLEBUFFERQUEUE, &player_buf_q);


		//(*player)->RegisterCallback(player, this->play_callback, nullptr); 
		//(*player)->SetCallbackEventsMask(player, SL_PLAYEVENT_HEADATEND);
	}
	bool Audio::checkPlaying(void)
	{
		//if( is_playing && is_done_buffer && current_time() - play_start_time > length_of_clip )
		std::vector<Sound*> toRemove;
		for(std::list<Sound>::iterator it = _playingSounds.begin(); it != _playingSounds.end(); it++)
		{
			_isDone = false;
			if((*it).update())
			{
				_isDone = true;
				toRemove.push_back(&*it);
			}
		}
		for(std::vector<Sound*>::iterator rit; rit != toRemove.end(); rit++)
		{
			_playingSounds.remove(*(*rit));
		}
		if(_isPlaying && _isDone)
		{
			(*player)->SetPlayState(player, SL_PLAYSTATE_STOPPED);
			(*player_buf_q)->Clear(player_buf_q);
			_isPlaying = false;
		}

	}
	void Audio::update(void)
	{
		checkPlaying();
		//TODO: Needs to go through _sounds to see if anything is still playing
		if(_isDone == true && _isPlaying == true) // If nothing is playing 
		{
			(*player_buf_q)->Clear(player_buf_q);
			_isPlaying = false;
		}
	}
	bool Audio::playSound(Sound * toPlay)
	{
		_playingSounds.push_back(*toPlay);
		(*player_buf_q)->Enqueue(player_buf_q, toPlay->clip_buffer, toPlay->clip_size);
		_playingSounds.back()._isPlaying = true;
		_playingSounds.back()._isDone = false;
		//toPlay->_isPlaying = true;
		//toPlay->_isDone = false;

		(*player)->SetPlayState(player, SL_PLAYSTATE_PLAYING);
		toPlay->timer.start();
		//play_start_time = current_time();
		return true;
	}
	Effect * Audio::createEffect(std::vector<unsigned char> * soundData)
	{
		_sounds.push_back(new Effect(soundData));
		return (Effect*)_sounds[_sounds.size()];
	}
	Audio::~Audio()
	{
		(*player_obj)->Destroy(player_obj);
		player_obj = nullptr;
		player = nullptr;
		player_vol = nullptr;
		player_buf_q = nullptr;

		(*_output_mix_obj)->Destroy(_output_mix_obj);
		_output_mix_obj = nullptr;
		_output_mix_vol = nullptr;
		(*_engine_obj)->Destroy(_engine_obj);
		_engine_obj = nullptr;
		_engine = nullptr;
	}
}