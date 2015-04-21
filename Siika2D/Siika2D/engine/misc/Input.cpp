#include "Input.h"

using namespace misc;

Input* Input::_instance = nullptr;

Input* Input::getInstance(android_app* app)
{
	if (_instance == nullptr)
	{
		_instance = new Input(app);
	}
	return _instance;
}


Input::Input(android_app* app)
{
	_touchingScreen = false;
	_app = app;
	initializeAccelerometer(app);
	initializeInput(app);
}

Input::~Input()
{
	_instance = nullptr;
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

void Input::initializeInput(android_app *app)
{
	app->onInputEvent = this->processInput;
}

int Input::processInput(android_app *app, AInputEvent *event)
{

	switch (AInputEvent_getType(event))
	{
		case AINPUT_EVENT_TYPE_KEY:
			_instance->processKey(event);
			break;

		case AINPUT_EVENT_TYPE_MOTION:
			_instance->processMotion(event);
			break;
	}

	return 1;
}

void Input::processKey(AInputEvent *event)
{
	if (AKeyEvent_getAction(event) == AKEY_EVENT_ACTION_DOWN)
	{
		KEY_CODE keyCode = (KEY_CODE)AKeyEvent_getKeyCode(event);

		std::vector<KEY_CODE>::iterator it = std::find(_instance->_keysDown.begin(), _instance->_keysDown.end(), keyCode);
		if (it == _instance->_keysDown.end())
			_instance->_keysDown.push_back(keyCode);
	}

	if (AKeyEvent_getAction(event) == AKEY_EVENT_ACTION_UP)
	{
		KEY_CODE keyCode = (KEY_CODE)AKeyEvent_getKeyCode(event);

		std::vector<KEY_CODE>::iterator it = std::find(_instance->_keysDown.begin(), _instance->_keysDown.end(), keyCode);
		if (it != _instance->_keysDown.end())
			_instance->_keysDown.erase(it);
	}
}

void Input::processMotion(AInputEvent *event)
{

	if (AMotionEvent_getAction(event) == AMOTION_EVENT_ACTION_MOVE)
	{
		glm::vec2 pos(AMotionEvent_getX(event, 0), AMotionEvent_getY(event, 0));
		_instance->_touchPosition = pos;
	}

	if (AMotionEvent_getAction(event) == AMOTION_EVENT_ACTION_DOWN)
	{
		_instance->_touchingScreen = true;
	}

	if (AMotionEvent_getAction(event) == AMOTION_EVENT_ACTION_UP)
	{
		_instance->_touchingScreen = false;
	}



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
