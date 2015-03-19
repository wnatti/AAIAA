#include "Siika2D.h"



void extern siika_main();

void android_main(android_app* app)
{
	core::Siika2D *siika = core::Siika2D::UI();
	siika->init(app);
	int animating = 1;
	int ident;
	int events;

	while (1)
	{
	
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
		}

	}
}