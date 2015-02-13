#pragma once
#include "../../native_app_glue/android_native_app_glue.h" //TODO: includeen projektiin siististi tämän jossain vaiheessa
#include "engine\graphics\GraphicsContext.h"
#include "engine\core\ResourceManager.h"
#include <android/sensor.h>
//#include "engine\core\MemoryManager.h"


/** 
	Singleton User interface for the engine's subsystems
	to be used everywhere engine's subsystems are needed
*/

struct saved_state {
	float angle;
	int32_t x;
	int32_t y;
};

class Siika2D
{
public:

	/**
		Pointter to the UI
	*/
	static Siika2D* UI();
	virtual ~Siika2D();
	bool init(android_app *app);
	void draw();
		
	ASensorManager* _sensorManager;
	const ASensor* _accelerometerSensor;
	saved_state svd_state;
	ASensorEventQueue* _sensorEventQueue;
protected:
	
	Siika2D();
	Siika2D(const Siika2D& s2d);
	Siika2D& operator=(const Siika2D& s2d);
		
	static Siika2D* _instance;

	core::ResourceManager _resourceManager;
	graphics::GraphicsContext _graphicsContext;
	android_app *_application;
		
};