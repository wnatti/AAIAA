#include "Siika2D.h"

void extern siika_main();

class Looper
{
public:

	Looper()
	{}

	~Looper()
	{}
	
	void loop(android_app *app)
	{
		while ((_ident = ALooper_pollAll(1, nullptr, &_events,
			(void**)&_source)) >= 0)
		{

			// Process this event.
			if (_source != NULL)
			{
				_source->process(app,_source);
			}
		}
	}

private:

	android_poll_source* _source;
	int _ident;
	int _events;

};


void android_main(android_app* app)
{
	app_dummy();
	core::Siika2D *siika = core::Siika2D::UI();
	siika->initialize(app);
	int animating = 1;
	int ident;
	int events;

	//Looper looper;

	while (1)
	{
		if (app->activityState != APP_CMD_STOP && siika->drawReady())
		siika_main();
	

		struct android_poll_source* source; //This goes to input

		while ((ident = ALooper_pollAll(animating ? 0 : -1, nullptr, &events,
			(void**)&source)) >= 0)
		{

			// Process this event.
			if (source != NULL)
			{
				source->process(app, source);
			}
			if (app->destroyRequested != 0)
			{
				return;
			}
			
		}
	}
}