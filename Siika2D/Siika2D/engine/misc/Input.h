#pragma once
#include "..\..\native_app_glue\android_native_app_glue.h"
#include "android\sensor.h"
#include "..\core\ErrorHandler.h"
#include <algorithm>
#include <glm.hpp>
#include <vector>

namespace core
{
	class Siika2D;
	class LooperManager;
}

enum INPUT_ID
{
	ACCELEROMETER = 10,
	TOUCH = 20
};


//TODO: more KEY_CODES
enum KEY_CODE
{
	KEYCODE_BUTTON_A = 96,
	KEYCODE_BUTTON_B = 97,
	KEYCODE_BUTTON_C = 98,
	KEYCODE_BUTTON_X = 99,
	KEYCODE_BUTTON_Y = 100,
	KEYCODE_BUTTON_Z = 101,
	KEYCODE_BUTTON_L1 = 102,
	KEYCODE_BUTTON_R1 = 103,
	KEYCODE_BUTTON_L2 = 104,
	KEYCODE_BUTTON_R2 = 105,


	KEYCODE_DPAD_UP = 19,
	KEYCODE_DPAD_DOWN = 20,
	KEYCODE_DPAD_LEFT = 21,
	KEYCODE_DPAD_RIGHT = 22,
	KEYCODE_DPAD_CENTER = 23,
	KEYCODE_VOLUME_UP = 24,
	KEYCODE_VOLUME_DOWN = 25,

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

		/**
			Sets the accelerometer active
		*/
		void enableAccelerometer();

		/**
			Sets the approx. tickrate/second for the accelerometer
		*/
		void setTickRate(float ticksPerSecond);

		/**
			Stops accelerometer processing
		*/
		void disableAccelerometer();

		std::vector<KEY_CODE> getDownKeys()
		{
			return _keysDown;
		}
		/**
			Is the screen being pressed?
		*/
		bool touchingScreen()
		{
			return _touchingScreen;
		}
		glm::vec2 getTouchPosition()
		{
			return _touchPosition;
		}
	protected:
		/**
			Is the screen being pressed
		*/
		bool _touchingScreen;
		/**
			Saved data depended on _tickRate
		*/
		std::vector < glm::vec3 > _accelerometerData;
		/**
			Analog keys currently pressed
		*/
		std::vector<KEY_CODE>_keysDown;
		/**
			Press location
		*/
		glm::vec2 _touchPosition;

		/**
			Processes accelerometer
		*/
		void processAccelerometer();
		
		void initializeAccelerometer(android_app *app);
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
	};

}