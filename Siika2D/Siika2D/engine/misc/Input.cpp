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
	initializeSensor(app,SENSOR_ID::ACCELEROMETER);
	initializeSensor(app, SENSOR_ID::GYROSCOPE);
	initializeInput(app);
}

Input::~Input()
{
	_instance = nullptr;
}

void Input::initializeSensor(android_app *app, SENSOR_ID sensorId)
{
	_sensorManager = ASensorManager_getInstance();

	switch (sensorId)
	{
	case ACCELEROMETER:
		_accelerometerSensor = ASensorManager_getDefaultSensor(_sensorManager, ASENSOR_TYPE_ACCELEROMETER);
		break;
	case GYROSCOPE:
		_gyroscopeSensor = ASensorManager_getDefaultSensor(_sensorManager, ASENSOR_TYPE_GYROSCOPE);
	}

	_sensorEventQueue = ASensorManager_createEventQueue(_sensorManager, _app->looper, sensorId, NULL, NULL);

}

void Input::enableSensor(SENSOR_ID sensorId)
{
	switch (sensorId)
	{
	case ACCELEROMETER:
		ASensorEventQueue_enableSensor(_sensorEventQueue, _accelerometerSensor);
		ASensorEventQueue_setEventRate(_sensorEventQueue, _accelerometerSensor, ((1000l / _tickRate) * 1000));
		break;
	case GYROSCOPE:
		ASensorEventQueue_enableSensor(_sensorEventQueue,_gyroscopeSensor);
		ASensorEventQueue_setEventRate(_sensorEventQueue, _gyroscopeSensor, ((1000l / _tickRate) * 1000));
	}
	
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
			_instance->processMotion(event, AInputEvent_getSource(event));
			break;
	}

	return 1;
}

void Input::processKey(AInputEvent *event)
{
	if (AKeyEvent_getAction(event) == AKEY_EVENT_ACTION_DOWN)
	{
		int keyCode = AKeyEvent_getKeyCode(event);

		std::vector<int>::iterator it = std::find(_instance->_keysDown.begin(), _instance->_keysDown.end(), keyCode);
		if (it == _instance->_keysDown.end())
			_instance->_keysDown.push_back(keyCode);
	}

	if (AKeyEvent_getAction(event) == AKEY_EVENT_ACTION_UP)
	{
		int keyCode = AKeyEvent_getKeyCode(event);

		std::vector<int>::iterator it = std::find(_instance->_keysDown.begin(), _instance->_keysDown.end(), keyCode);
		if (it != _instance->_keysDown.end())
			_instance->_keysDown.erase(it);
	}
}

void Input::processMotion(AInputEvent *event, int source)
{
	if (source == AINPUT_SOURCE_TOUCHSCREEN)
		processTouchscreen(event);

	if (source == AINPUT_SOURCE_DPAD || source == AINPUT_SOURCE_TRACKBALL || source == 16777232)
		processStickOrDpad(event);
}

void Input::processTouchscreen(AInputEvent *event)
{
	
	_fingersDown = AMotionEvent_getPointerCount(event);

	for (int i = 0; i < _fingersDown; i++)
	{
		if (AMotionEvent_getAction(event) == AMOTION_EVENT_ACTION_MOVE)
		{
			glm::vec2 pos(AMotionEvent_getX(event, i), AMotionEvent_getY(event, i));
			_instance->_fingers[i]._positionCurrent = pos;
		}

		if (AMotionEvent_getAction(event) == AMOTION_EVENT_ACTION_DOWN)
		{
			glm::vec2 pos(AMotionEvent_getX(event, 0), AMotionEvent_getY(event, 0));
			_instance->_fingers[i]._positionStart = pos;

		}
		if (AMotionEvent_getAction(event) == AMOTION_EVENT_ACTION_UP)
		{
			glm::vec2 pos(AMotionEvent_getX(event, i), AMotionEvent_getY(event, i));
			_instance->_fingers[i]._positionEnd = pos;
		}
	}

}

void Input::processStickOrDpad(AInputEvent *event)
{
	_sticksActive = AMotionEvent_getPointerCount(event);

	for (int i = 0; i < _sticksActive; i++)
	{
		if (AMotionEvent_getAction(event) == AMOTION_EVENT_ACTION_MOVE)
		{
			float orientation(AMotionEvent_getOrientation(event,i));
			float x = AMotionEvent_getX(event, i);
			x;
			s2d_info("%f", orientation);
			AINPUT_MOTION_RANGE_Y;
			_instance->_sticks->_pointingDirection = orientation;
		}

		if (AMotionEvent_getAction(event) == AMOTION_EVENT_ACTION_DOWN)
		{
			float orientation(AMotionEvent_getOrientation(event, i));
			_instance->_sticks->_pointingDirection = orientation;
			_instance->_sticks->_pressedDown = true;
		}

		if (AMotionEvent_getAction(event) == AMOTION_EVENT_ACTION_UP)
		{
			float orientation(AMotionEvent_getOrientation(event, i));
			_instance->_sticks->_pointingDirection = orientation;
			_instance->_sticks->_pressedDown = false;
		}
	}
}

void Input::setTickRate(float ticksPerSecond)
{
	_tickRate = ticksPerSecond;
}

void Input::accelerometerDisable()
{
	ASensorEventQueue_disableSensor(_sensorEventQueue, _accelerometerSensor);
}

void Input::processAccelerometer()
{
	ASensorEvent event;
	_accelerometerData = nullptr;

	while (ASensorEventQueue_getEvents(_sensorEventQueue, &event, 1) > 0)
	{
		*_accelerometerData = event.acceleration;
	}

}

void Input::processGyroscope()
{
	ASensorEvent event;
	_gyroscopeData = nullptr;

	while (ASensorEventQueue_getEvents(_sensorEventQueue, &event, 1) > 0)
	{
		*_gyroscopeData = event.acceleration;
	}

}
