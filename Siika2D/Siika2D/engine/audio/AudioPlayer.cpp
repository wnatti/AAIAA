#include "AudioPlayer.h"
#include "../core/ErrorHandler.h"

using namespace audio;

AudioPlayer::AudioPlayer(AudioPlayer* pointer)
{
	_audioAsset = pointer->_audioAsset;
}

AudioPlayer::~AudioPlayer()
{
	if (audioPlayerObj != nullptr)
	{
		(*audioPlayerObj)->Destroy(audioPlayerObj);

		audioPlayerObj = nullptr;
		audioPlayerPlay = nullptr;
		audioPlayerSeek = nullptr;
		audioPlayerVol = nullptr;
	}
}

SLuint32 AudioPlayer::GetPlayState()
{
	SLuint32 tempReturnValue;
	result = (*audioPlayerPlay)->GetPlayState(audioPlayerPlay, &tempReturnValue);
	s2d_assert(result == SL_RESULT_SUCCESS);

	return tempReturnValue;
}

void AudioPlayer::SetPlayState(SLuint32 state)
{
	if(audioPlayerPlay != nullptr)
	{
		result = (*audioPlayerPlay)->SetPlayState(audioPlayerPlay, state);
		s2d_assert(result == SL_RESULT_SUCCESS);
	}
}

void AudioPlayer::SetLooping(bool isEnabled)
{
	result = (*audioPlayerSeek)->SetLoop(audioPlayerSeek, isEnabled ? SL_BOOLEAN_TRUE : SL_BOOLEAN_FALSE, 0, SL_TIME_UNKNOWN);
	s2d_assert(result == SL_RESULT_SUCCESS);
}

void AudioPlayer::SetVolume(float volPercentage)
{
	SLmillibel tempVol;
	result = (*audioPlayerVol)->GetMaxVolumeLevel(audioPlayerVol, &tempVol);

	tempVol *= 0.01 * volPercentage;

	result = (*audioPlayerVol)->SetVolumeLevel(audioPlayerVol, tempVol);
	s2d_assert(result == SL_RESULT_SUCCESS);
}