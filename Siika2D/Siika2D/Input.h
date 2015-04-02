#pragma once
#include "native_app_glue\android_native_app_glue.h"
#include "android\sensor.h"
#include <vec3.hpp>
#include <vector>

namespace core
{
	class Siika2D;
	class LooperManager;
}

enum INPUT_ID
{
	ACCELEROMETER = 10
};

namespace misc
{

	class Input
	{

	friend class core::Siika2D;

	public:

		std::vector < glm::vec3 > _accelerometerData;
		void enableAccelerometer();
		void setTickRate(float ticksPerSecond);
		void disableAccelerometer();

	private:
		bool _accelerometerEnabled = false;
		float _tickRate = 1.0;
		Input(android_app* app);
		void processAccelerometer();
		void initializeAccelerometer(android_app* app);
		void processKey(AInputEvent* event);
		void processMotion(AInputEvent* event);
		AInputQueue* _inputQueue;
		ALooper* _looper;
		android_app *_app;
		~Input();
		ASensorEventQueue* _sensorEventQueue;
		ASensorManager* _sensorManager;
		const ASensor* _accelerometerSensor;
	};

}