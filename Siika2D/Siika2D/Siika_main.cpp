#include "Siika2D.h"
#include "Input.h"
#include "engine\graphics\Buffer.h"
#include "LooperManager.h"
void extern siika_main();

#pragma once
namespace core
{
	class AndroidInterface
	{

	public:
		AndroidInterface()
		{}
		void initialize(android_app *app)
		{
			_siika->initialize(app);
		}
		~AndroidInterface()
		{}

		void processAndroidCmds(android_app* app)
		{
			_siika->loop(app);
		}

		core::Siika2D *_siika;
	};
}

void android_main(android_app* app)
{
	app_dummy();
	core::AndroidInterface AIF;
	AIF._siika = core::Siika2D::UI();
	AIF.initialize(app);

	while (!app->destroyRequested)
	{
		if (app->activityState != APP_CMD_STOP && AIF._siika->drawReady() == true)
			siika_main();

		AIF.processAndroidCmds(app);
	}
}
	