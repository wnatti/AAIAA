#include "AudioInitializer.h"
#include "../core/ErrorHandler.h"

using namespace audio;

AudioInitializer* AudioInitializer::instance = nullptr;

void AudioPlayerCallback(SLPlayItf playerObject, void* context, SLuint32 event)
{
	s2d_info(("AudioPlayer callback called."));

	if (event == SL_PLAYEVENT_HEADATEND)
	{
		s2d_info(("AudioPlayer callback event: SL_PLAYEVENT_HEADATED."));
		(*playerObject)->SetPlayState(playerObject, SL_PLAYSTATE_STOPPED);
	}
}

AudioInitializer* AudioInitializer::GetInstance()
{
	if (instance == nullptr)
		instance = new AudioInitializer();

	return instance;
}

void AudioInitializer::InitAudioPlayer(AudioPlayer* player)
{
	SLDataLocator_AndroidFD locator = { SL_DATALOCATOR_ANDROIDFD, player->getAudioAsset()->fileDescriptor, player->getAudioAsset()->start, player->getAudioAsset()->length };
	SLDataFormat_MIME format = { SL_DATAFORMAT_MIME, nullptr, SL_CONTAINERTYPE_UNSPECIFIED };
	SLDataSource audioSrc = { &locator, &format };

	SLDataLocator_OutputMix tempOutmix = { SL_DATALOCATOR_OUTPUTMIX, outputMixObj };
	SLDataSink tempAudioSink = { &tempOutmix, nullptr };

	const SLInterfaceID tempIds[3] = { SL_IID_PLAY, SL_IID_SEEK, SL_IID_VOLUME };
	const SLboolean tempReq[3] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };

	result = (*engine)->CreateAudioPlayer(engine, &player->audioPlayerObj, &audioSrc, &tempAudioSink, 3, tempIds, tempReq);
	s2d_assert(result == SL_RESULT_SUCCESS);

	result = (*player->audioPlayerObj)->Realize(player->audioPlayerObj, SL_BOOLEAN_FALSE);
	s2d_assert(result == SL_RESULT_SUCCESS);

	result = (*player->audioPlayerObj)->GetInterface(player->audioPlayerObj, SL_IID_PLAY, &player->audioPlayerPlay);
	s2d_assert(result == SL_RESULT_SUCCESS);

	result = (*player->audioPlayerObj)->GetInterface(player->audioPlayerObj, SL_IID_SEEK, &player->audioPlayerSeek);
	s2d_assert(result == SL_RESULT_SUCCESS);

	result = (*player->audioPlayerObj)->GetInterface(player->audioPlayerObj, SL_IID_VOLUME, &player->audioPlayerVol);
	s2d_assert(result == SL_RESULT_SUCCESS);

	result = (*player->audioPlayerPlay)->RegisterCallback(player->audioPlayerPlay, AudioPlayerCallback, NULL);
	s2d_assert(result == SL_RESULT_SUCCESS);

	result = (*player->audioPlayerPlay)->SetCallbackEventsMask(player->audioPlayerPlay, SL_PLAYEVENT_HEADATEND);
	s2d_assert(result == SL_RESULT_SUCCESS);

}

void AudioInitializer::CreateEngine()
{
	result = slCreateEngine(&engineObj, 0, nullptr, 0, nullptr, nullptr);
	s2d_assert(result == SL_RESULT_SUCCESS);

	result = (*engineObj)->Realize(engineObj, SL_BOOLEAN_FALSE);
	s2d_assert(result == SL_RESULT_SUCCESS);

	result = (*engineObj)->GetInterface(engineObj, SL_IID_ENGINE, &engine);
	s2d_assert(result == SL_RESULT_SUCCESS);

	result = (*engine)->CreateOutputMix(engine, &outputMixObj, 0, NULL, NULL);
	s2d_assert(result == SL_RESULT_SUCCESS);

	result = (*outputMixObj)->Realize(outputMixObj, SL_BOOLEAN_FALSE);
	s2d_assert(result == SL_RESULT_SUCCESS);
}

AudioInitializer::AudioInitializer()
{
	CreateEngine();
}

AudioInitializer::~AudioInitializer()
{
	if (outputMixObj != nullptr)
	{
		(*outputMixObj)->Destroy(outputMixObj);

		outputMixObj = nullptr;
		outputMixVol = nullptr;
	}

	if(engineObj != nullptr)
	{
		(*engineObj)->Destroy(engineObj);

		engineObj = nullptr;
		engine = nullptr;
	}
}