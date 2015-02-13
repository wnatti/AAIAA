#pragma once
#include "../../native_app_glue/android_native_app_glue.h" //TODO: includeen projektiin siististi tämän jossain vaiheessa
#include "engine\graphics\GraphicsContext.h"


/** User interface for the engine's subsystems

*/

class Siika2D
{
public:
	Siika2D();
	~Siika2D();
	void initialize();
private:
	GraphicsContext _graphicsContext;
	void initGraphicsContext();
	android_app *_application;
};