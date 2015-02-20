/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

//BEGIN_INCLUDE(all)
#include "../Siika2D.h"
#include <jni.h>
#include <errno.h>
#include <EGL/egl.h>
#include <glm.hpp>
#include <GLES2\gl2.h>
#include <lodepng.h>
#include <android/sensor.h>
#include <android/log.h>
#include "../Siika2D.h"
#include "../engine/core/ErrorHandler.h"
#include "../native_app_glue/android_native_app_glue.h"
#include "../engine/core/ResourceManager.h"
#include "../engine/graphics/GraphicsContext.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))



void android_main(struct android_app* app)
{
	
	Siika2D *siika = Siika2D::UI(app);

	//Tässä oli inputtia

	// loop waiting for stuff to do.
	int animating = 1;
	bool running = true;
	while (!siika->wantsToExit()) 
	{
		// Read all pending events.
		int ident;
		int events;
		struct android_poll_source* source; //This goes to input

		// If not animating, we will block forever waiting for events.
		// If animating, we loop until all events are read, then continue
		// to draw the next frame of animation.
		while ((ident = ALooper_pollAll(animating ? 0 : -1, nullptr, &events,
			(void**)&source)) >= 0)
		{

			// Process this event.
			if (source != NULL) {
				source->process(app, source);
			}

			// If a sensor has data, process it now.
			//if (ident == LOOPER_ID_USER) {
			//	if (siika->_accelerometerSensor != NULL) {
			//		ASensorEvent event;
			//		while (ASensorEventQueue_getEvents(siika->_sensorEventQueue,
			//			&event, 1) > 0) {
			//			LOGI("accelerometer: x=%f y=%f z=%f",
			//				event.acceleration.x, event.acceleration.y,
			//				event.acceleration.z);
			//		}
			//	}
			//}

			// Check if we are exiting.
		}

		//Here was animation

		//Here draw
		siika->draw();
	}
}