#include "Input.h"
#include "engine\core\ErrorHandler.h"
using namespace misc;

Input::Input(android_app* app)
{
	_app = app;
}


Input::~Input()
{

}



void Input::initializeAccelerometer(android_app* app)
{
	_sensorManager = ASensorManager_getInstance();
	_accelerometerSensor = ASensorManager_getDefaultSensor(_sensorManager, ASENSOR_TYPE_ACCELEROMETER);
	_sensorEventQueue = ASensorManager_createEventQueue(_sensorManager, app->looper,INPUT_ID::ACCELEROMETER, NULL, NULL);
}

void Input::enableAccelerometer()
{
	initializeAccelerometer(_app);
	ASensorEventQueue_enableSensor(_sensorEventQueue, _accelerometerSensor);
	ASensorEventQueue_setEventRate(_sensorEventQueue, _accelerometerSensor, ((1000l/_tickRate)*1000));
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

void Input::processMotion(AInputEvent* event)
{

}