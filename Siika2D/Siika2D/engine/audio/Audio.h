#pragma once
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

// http://vec3.ca/getting-started-with-opensl-on-android/
// https://audioprograming.wordpress.com/2012/03/03/android-audio-streaming-with-opensl-es-and-the-ndk/

class Audio
{
	friend class Sound;
public:
	Audio();
	~Audio(){};
	void createPlayer(void);
	bool checkPlaying(void);
	void SLAPIENTRY play_callback(SLPlayItf player,	void *context, SLuint32 event)
	{
		if(event & SL_PLAYEVENT_HEADATEND)
			_isDone = true;
	}
private:
	SLObjectItf _engine_obj;
	SLEngineItf _engine;
	SLObjectItf _output_mix_obj;
	SLVolumeItf _output_mix_vol;

	SLAndroidSimpleBufferQueueItf player_buf_q;
	SLObjectItf player_obj;
	SLPlayItf player;
	SLVolumeItf player_vol;

	bool _isPlaying, _isDone;
};

class Sound
{
public:
	Sound(){};
	void setAudioDevice(Audio * audioDevice){ _ad = audioDevice; }; // Constructoriin? Onko t‰lle mit‰‰n fiksumpaa tapaa ? 
	~Sound(){};
	
	void play(void);
private:
	Audio *_ad;
	const void *clip_samples;             //the raw samples
	unsigned int clip_num_samples;        //how many samples there are
	unsigned int clip_samples_per_sec;    //the sample rate in Hz
	void * clip_buffer;
	SLuint32 clip_size;
};

class Track:Sound
{
public:
	Track(){};
	~Track(){};

private:

};

class Effect:Sound
{
public:
	Effect(){};
	~Effect(){};

private:

};