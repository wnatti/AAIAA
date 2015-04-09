#include "Audio.h"

Audio::Audio()
{

	//Jokin menee vikaan..
	/*
	slCreateEngine(&_engine_obj, 0, nullptr, 0, nullptr, nullptr);
	(*_engine_obj)->Realize(_engine_obj, SL_BOOLEAN_FALSE);
	(*_engine_obj)->GetInterface(_engine_obj, SL_IID_ENGINE, &_engine);


	const SLInterfaceID ids[] = { SL_IID_VOLUME };
	const SLboolean req[] = { SL_BOOLEAN_FALSE };

	(*_engine)->CreateOutputMix(_engine, &_output_mix_obj, 1, ids, req);

	(*_output_mix_obj)->Realize(_output_mix_obj, SL_BOOLEAN_FALSE);

	if((*_output_mix_obj)->GetInterface(_output_mix_obj,
		SL_IID_VOLUME, &_output_mix_vol) != SL_RESULT_SUCCESS)
		_output_mix_vol = nullptr;
	*/
}

