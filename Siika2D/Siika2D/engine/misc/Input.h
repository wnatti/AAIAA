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

	class Input
	{

	friend class core::Siika2D;

	public:

		static Input* getInstance(android_app *app);
		virtual ~Input();

		std::vector < glm::vec3 > _accelerometerData;
		void enableAccelerometer();
		void setTickRate(float ticksPerSecond);
		void disableAccelerometer();
		std::vector<KEY_CODE> getDownKeys()
		{
			return _keysDown;
		}

		bool touchingScreen()
		{
			return _touchingScreen;
		}
		glm::vec2 getTouchPosition()
		{
			return _touchPosition;
		}
	protected:
		bool _touchingScreen;
		std::vector<KEY_CODE>_keysDown;
		glm::vec2 _touchPosition;
		void processAccelerometer();
		void initializeAccelerometer(android_app *app);
		void initializeInput(android_app *app);
		static int processKey(android_app *app, AInputEvent *event);
		void processMotion(AInputEvent *event);

		//Input();
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