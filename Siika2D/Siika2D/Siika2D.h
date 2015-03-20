#pragma once
#include "../../native_app_glue/android_native_app_glue.h" //TODO: includeen projektiin siististi tämän jossain vaiheessa
#include "engine\core\ResourceManager.h"
#include "engine\graphics\Graphics.h"
#include <android/sensor.h>
//#include "engine\core\MemoryManager.h"


/** 
	Singleton User interface used for the engine's subsystems.
	To be used everywhere engine's subsystems are needed
*/
namespace core
{


	struct saved_state {
		float angle;
		int32_t x;
		int32_t y;
	};

	class Siika2D
	{
		//friend class Graphics;

	public:

		/**
			Pointter to the UI
			*/
		static Siika2D* UI();
		virtual ~Siika2D();


		ASensorManager* _sensorManager;
		const ASensor* _accelerometerSensor;
		saved_state* _savedState;
		ASensorEventQueue* _sensorEventQueue;

		/**
			Tells when graphics has been initialized
			*/
		bool drawReady()
		{
			return _drawReady;
		}
		/**
			Initializes siika, this should only happen in Siika_main.cpp
		*/
		void initialize(android_app *app);



		graphics::Graphics *GRAPHICS;


	protected:
		Siika2D();
		Siika2D(const Siika2D& s2d);
		Siika2D& operator=(const Siika2D& s2d);
		static Siika2D* _instance;

		android_app *_application;
		//std::vector<int> _appCommandList;

		static void processCommands(android_app* app, int32_t command);
		void initializeGraphics();
		void terminateGraphics();
		void terminate();
		
		void saveState(android_app *app);
		void loadState(android_app *app);
		void getLatestState(android_app *app);

		core::ResourceManager _resourceManager;
		bool _drawReady;

	};
}
