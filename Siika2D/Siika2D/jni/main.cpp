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

/**
 * Our saved state data.
 */
//struct saved_state {
//    float angle;
//    int32_t x;
//    int32_t y;
//};

/**
 * Shared state for our app.
 */
struct engine
{
	struct android_app* app;

    ASensorManager* sensorManager;
    const ASensor* accelerometerSensor;
    ASensorEventQueue* sensorEventQueue;

    int animating;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    int32_t width;
    int32_t height;
    struct saved_state state;
};

//static int engine_init_display(struct engine* engine)
//{
//
//	//NOTE: THIS IS A HACK UNTIL ENGINE_UI IS DONE
//	engine->display = engine->Mycontext._display;
//	engine->context = engine->Mycontext._context;
//	engine->surface = engine->Mycontext._surface;
//	engine->width = engine->Mycontext._width;
//	engine->height = engine->Mycontext._height;
//	engine->state.angle = 0;
//	
//}


/**
 * Just the current frame in the display.
 */
static void engine_draw_frame(struct engine* engine)
{
  
}


/**
 * Process the next input event.
 */
//static int32_t engine_handle_input(struct android_app* app, AInputEvent* event) {
//    struct engine* engine = (struct engine*)app->userData;
//    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
//        engine->animating = 1;
//        engine->state.x = AMotionEvent_getX(event, 0);
//        engine->state.y = AMotionEvent_getY(event, 0);
//        return 1;
//    }
//    return 0;
//}

/**
 * Process the next main command.
 */
//static void engine_handle_cmd(struct android_app* app, int32_t cmd) {
//    struct engine* engine = (struct engine*)app->userData;
//    switch (cmd) {
//        case APP_CMD_SAVE_STATE:
//            // The system has asked us to save our current state.  Do so.
//            engine->app->savedState = malloc(sizeof(struct saved_state));
//            *((struct saved_state*)engine->app->savedState) = engine->state;
//            engine->app->savedStateSize = sizeof(struct saved_state);
//            break;
//        case APP_CMD_INIT_WINDOW:
//            // The window is being shown, get it ready.
//            if (engine->app->window != NULL) {
//                engine_init_display(engine);
//                engine_draw_frame(engine);
//            }
//            break;
//        case APP_CMD_TERM_WINDOW:
//            // The window is being hidden or closed, clean it up.
//            engine_term_display(engine);
//            break;
//        case APP_CMD_GAINED_FOCUS:
//            // When our app gains focus, we start monitoring the accelerometer.
//            if (engine->accelerometerSensor != NULL) {
//                ASensorEventQueue_enableSensor(engine->sensorEventQueue,
//                        engine->accelerometerSensor);
//                // We'd like to get 60 events per second (in us).
//                ASensorEventQueue_setEventRate(engine->sensorEventQueue,
//                        engine->accelerometerSensor, (1000L/60)*1000);
//            }
//            break;
//        case APP_CMD_LOST_FOCUS:
//            // When our app loses focus, we stop monitoring the accelerometer.
//            // This is to avoid consuming battery while not being used.
//            if (engine->accelerometerSensor != NULL) {
//                ASensorEventQueue_disableSensor(engine->sensorEventQueue,
//                        engine->accelerometerSensor);
//            }
//            // Also stop animating.
//            engine->animating = 0;
//            engine_draw_frame(engine);
//            break;
//    }
//}

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */



void android_main(struct android_app* app)
{
	Siika2D *siika = Siika2D::UI();

	siika->init(app);
	while (1)
	{
		
	}
	
	app->userData = &siika; //not necessarily necessary
   // app->onAppCmd = engine_handle_cmd;
    //app->onInputEvent = engine_handle_input;
	siika->init(app);

   //Tässä oli inputtia

    if (app->savedState != nullptr)
	{
        // We are starting with a previous saved state; restore from it.
        siika->svd_state = *(struct saved_state*)app->savedState;
    }

    // loop waiting for stuff to do.
	int animating = 1;
	bool running = true;
    while (running) {
        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source* source; //This goes to input

        // If not animating, we will block forever waiting for events.
        // If animating, we loop until all events are read, then continue
        // to draw the next frame of animation.
        while ((ident=ALooper_pollAll(animating ? 0 : -1, nullptr, &events,
                (void**)&source)) >= 0) {

            // Process this event.
            if (source != NULL) {
                source->process(app, source);
            }

            // If a sensor has data, process it now.
            if (ident == LOOPER_ID_USER) {
                if (siika->_accelerometerSensor != NULL) {
                    ASensorEvent event;
                    while (ASensorEventQueue_getEvents(siika->_sensorEventQueue,
                            &event, 1) > 0) {
                        LOGI("accelerometer: x=%f y=%f z=%f",
                                event.acceleration.x, event.acceleration.y,
                                event.acceleration.z);
                    }
                }
            }

            // Check if we are exiting.
            if (app->destroyRequested != 0) {
				running = false;
                return;
            }
        }

			//Here was animation

			//Here draw
		siika->draw();
        }
}

//END_INCLUDE(all)
