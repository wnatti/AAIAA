#include "Input.h"

using namespace misc;

Input::Input(android_app* app)
{
	_app = app;
	initializeAccelerometer(app);
	enableTouch(app);
}

Input::~Input()
{

}

void Input::initializeAccelerometer(android_app *app)
{
	_sensorManager = ASensorManager_getInstance();
	_accelerometerSensor = ASensorManager_getDefaultSensor(_sensorManager, ASENSOR_TYPE_ACCELEROMETER);
	_sensorEventQueue = ASensorManager_createEventQueue(_sensorManager, _app->looper, INPUT_ID::ACCELEROMETER, NULL, NULL);
}

void Input::enableAccelerometer()
{
	ASensorEventQueue_enableSensor(_sensorEventQueue, _accelerometerSensor);
	ASensorEventQueue_setEventRate(_sensorEventQueue, _accelerometerSensor, ((1000l / _tickRate) * 1000));
}

void Input::enableTouch(android_app *app)
{
	_inputQueue = app->inputQueue;
}

void Input::disableTouch()
{
}

void Input::processTouch()
{
	android_poll_source source = _app->inputPollSource;
	int id;
	int events;

		AInputEvent *event;

		while (AInputQueue_getEvent(_inputQueue, &event) > 0)
		{
			switch (AInputEvent_getType(event))
			{
			case AINPUT_EVENT_TYPE_KEY:
				processKey(event);
				break;

			case AINPUT_EVENT_TYPE_MOTION:
				processMotion(event);
				break;

			}
		}
}

void Input::processKey(AInputEvent *event)
{
	if (AKeyEvent_getAction(event) == AKEY_EVENT_ACTION_DOWN)
	{
		KEY_CODE keyCode = (KEY_CODE)AKeyEvent_getKeyCode(event);
		_keysDown.push_back(keyCode);
	}

	if (AKeyEvent_getAction(event) == AKEY_EVENT_ACTION_UP)
	{
		KEY_CODE keyCode = (KEY_CODE)AKeyEvent_getKeyCode(event);

		std::vector<KEY_CODE>::iterator it = std::find(_keysDown.begin(), _keysDown.end(), keyCode);
		if (it != _keysDown.end())
			_keysDown.erase(it);
	}
}

void Input::processMotion(AInputEvent *event)
{

}

void Input::setTickRate(float ticksPerSecond)
{
	_tickRate = ticksPerSecond;
}

void Input::disableAccelerometer()
{
	ASensorEventQueue_disableSensor(_sensorEventQueue, _accelerometerSensor);
}

void Input::processAccelerometer()
{
	ASensorEvent event;
	_accelerometerData.clear();

	glm::vec3 data;
	while (ASensorEventQueue_getEvents(_sensorEventQueue, &event, 1) > 0)
	{
		data.x = event.acceleration.x;
		data.y = event.acceleration.y;
		data.z = event.acceleration.z;
		_accelerometerData.push_back(data);
	}

}
