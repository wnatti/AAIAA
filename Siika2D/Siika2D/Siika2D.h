#pragma once
#include "../../native_app_glue/android_native_app_glue.h" //TODO: includeen projektiin siististi tämän jossain vaiheessa
#include "engine\graphics\GraphicsContext.h"
#include "engine\core\ResourceManager.h"
#include <android/sensor.h>
//#include "engine\core\MemoryManager.h"


/** 
	Singleton User interface used for the engine's subsystems.
	To be used everywhere engine's subsystems are needed
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
	static Siika2D* UI(android_app* app);
	virtual ~Siika2D();
	bool init(android_app *app);

	/**
		Asks if siika wants to die
	*/
	bool wantsToExit()
	{
		return _exitRequested;
	}
	void draw(); //TODO: Graphics luokka jolle piirto?
	
	ASensorManager* _sensorManager;
	const ASensor* _accelerometerSensor;
	saved_state _savedState;
	ASensorEventQueue* _sensorEventQueue;
	static void processCommands(android_app* app, int32_t command);
protected:
	bool _exitRequested;
	Siika2D(android_app* app);
	Siika2D(const Siika2D& s2d);
	Siika2D& operator=(const Siika2D& s2d);
	void addApplicationCommand();
	static Siika2D* _instance;

	core::ResourceManager _resourceManager;
	graphics::GraphicsContext _graphicsContext;
	android_app *_application;
	std::vector<int> _appCommandList;
		
};