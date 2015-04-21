#pragma once
#include "../../native_app_glue/android_native_app_glue.h" //TODO: includeen projektiin siististi tämän jossain vaiheessa
#include "ResourceManager.h"
#include "../graphics/Graphics.h"
#include <android/sensor.h>
#include "../misc/Input.h"
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
		friend class AndroidInterface;

	public:


		/**
			Pointter to the UI
		*/
		static Siika2D* UI();
		virtual ~Siika2D();

		saved_state* _savedState;	

		/**
			Tells when graphics has been initialized
		*/
		bool drawReady()
		{
			return _drawReady;
		}

		graphics::Graphics *GRAPHICS;
		misc::Input *INPUT;
		core::ResourceManager _resourceManager;
	protected:
		Siika2D();
		Siika2D(const Siika2D& s2d);
		Siika2D& operator=(const Siika2D& s2d);
		static Siika2D* _instance;

		android_app *_application;
		//std::vector<int> _appCommandList;

		static void processCommands(android_app* app, int32_t command);

		/**
			Create a Graphics class if ran the first time.
			Else initializes wiped Graphics context to a new display.
		*/
		void initializeGraphics();

		void initializeInput();

		void terminateInput();
		/**
			Wipes the graphics context only.
		*/
		void terminateGraphics();
		void terminate();
		
		/**
			Saves the application to the system memory,
			when the user decides to switch away from the application.
		*/
		void saveState(android_app *app);

		/**
			Gets the saved application if there is one.
		*/
		void loadState(android_app *app);
		bool _drawReady;

		void run(android_app* app);

		/**
			Initializes siika, this should only happen in Siika_main.cpp
		*/
		void initialize(android_app *app);

	};
}
