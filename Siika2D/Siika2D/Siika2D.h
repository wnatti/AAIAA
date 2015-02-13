#pragma once
#include "../../native_app_glue/android_native_app_glue.h" //TODO: includeen projektiin siististi tämän jossain vaiheessa
#include "engine\graphics\GraphicsContext.h"
#include "engine\core\ResourceManager.h"
//#include "engine\core\MemoryManager.h"


/** User interface for the engine's subsystems

*/

class Siika2D
{
public:
	static Siika2D* getInstance();
	virtual ~Siika2D();
	
private:

	Siika2D();

	Siika2D(const Siika2D& s2d);
	Siika2D& operator=(const Siika2D& s2d);

	static Siika2D* _instance;

	core::ResourceManager _resourceManager;
	GraphicsContext _graphicsContext;
	android_app *_application;
};