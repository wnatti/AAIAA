#pragma once
#include "../../native_app_glue/android_native_app_glue.h" //TODO: includeen projektiin siististi tämän jossain vaiheessa
#include "engine\graphics\GraphicsContext.h"
//#include "engine/core/MemoryManager.h"
#include "engine\core\ResourceManager.h"


/** 
	User interface class for the engine's subsystems
*/

class Siika2D
{
public:
	Siika2D();
	~Siika2D();

	/**
		Initializes all subsystems
	*/
	void initialize();

private:


	/**
		Initializes Graphics context
	*/
	void initGraphicsContext();
	android_app *_application;
	GraphicsContext _graphicsContext;
	core::ResourceManager _resourceManager;
	AAssetManager* _androidAssetManager;
};