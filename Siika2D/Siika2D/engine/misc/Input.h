#pragma once
#include "..\..\native_app_glue\android_native_app_glue.h"
#include "android\sensor.h"
#include "..\core\ErrorHandler.h"
#include <algorithm>
#include <glm.hpp>
#include <vector>
#include "android\keycodes.h"

namespace core
{
	class Siika2D;
	class LooperManager;
}

enum SENSOR_ID
{
	ACCELEROMETER = 10,
	GYROSCOPE = 20
};

struct Finger
{

	/**
		Current press location
	*/
	glm::vec2 _touchPositionCurrent = glm::vec2(0.f, 0.f);

	/**
		Location where the last touch event started
	*/
	glm::vec2 _touchPositionStart = glm::vec2(0.f, 0.f);

	/**
		Location where the touch event ended
	*/
	glm::vec2 _touchPositionEnd = glm::vec2(0.f, 0.f);

};


namespace misc
{
	/**
		Singleton class that handles all the input coming from the device
							Used from Siika2D-class
	*/
	class Input
	{

	friend class core::Siika2D;

	public:

		static Input* getInstance(android_app *app);
		virtual ~Input();

		ASensorVector *_accelerometerData;

		ASensorVector *_gyroscopeData;

		/**
			Sets the sensor active
		*/
		void enableSensor(SENSOR_ID sensorId);

		/**
			Sets the approx. tickrate/second for the accelerometer
		*/
		void setTickRate(float ticksPerSecond);

		/**
			Stops accelerometer processing
		*/
		void accelerometerDisable();

		std::vector<int> getDownKeys()
		{
			return _keysDown;
		}
		/**
			Is the screen being pressed?
		*/
		bool touchingScreen()
		{
			return _fingersDown;
		}

		glm::vec2 touchPositionCurrent(int finger)
		{
			return _fingers[finger]._touchPositionCurrent;
		}

		glm::vec2 touchPositionStart(int finger)
		{
			return _fingers[finger]._touchPositionStart;
		}

		glm::vec2 touchPositionEnd(int finger)
		{
			return _fingers[finger]._touchPositionEnd;
		}
	protected:
		/**
			Is the screen being pressed
		*/
		bool _touchingScreen;

		/**
			Analog keys currently pressed
		*/
		std::vector<int>_keysDown;


		Finger _fingers[2];

		int _fingersDown;

		/**
			Processes accelerometer
		*/
		void processAccelerometer();

		void processGyroscope();

		void initializeGyroscope(android_app *app);

		void initializeSensor(android_app *app, SENSOR_ID sensorId);
		/**
			Sets processInput to read Android -device's input-data
		*/
		void initializeInput(android_app *app);
		/**
			Processes the device's latest data
		*/
		static int processInput(android_app *app, AInputEvent *event);
		/**
			Processes key-input
		*/
		void processKey(AInputEvent *event);
		/**
			Processes motion-input
		*/
		void processMotion(AInputEvent *event);

		Input(android_app* app);
		Input(const Input& input);
		Input& operator=(const Input& input);
		static Input* _instance;

		bool _accelerometerEnabled = false;
		float _tickRate = 1.0;

		android_app *_app;
		ASensorEventQueue* _sensorEventQueue;
		ASensorManager* _sensorManager;
		const ASensor* _accelerometerSensor;
		const ASensor* _gyroscopeSensor;
	};

}