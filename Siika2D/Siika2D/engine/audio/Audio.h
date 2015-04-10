#pragma once
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

// http://vec3.ca/getting-started-with-opensl-on-android/

class Audio
{
public:
	Audio();
	~Audio(){};

private:
	SLObjectItf _engine_obj;
	SLEngineItf _engine;
	SLObjectItf _output_mix_obj;
	SLVolumeItf _output_mix_vol;
};

class sound
{
public:
	sound(){};
	~sound(){};

private:
};

class track:sound
{
public:
	track(){};
	~track(){};

private:
};

class effect:sound
{
public:
	effect(){};
	~effect(){};

private:

};