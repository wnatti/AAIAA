#include "Siika2D.h"

Siika2D* Siika2D::_instance = nullptr;

Siika2D* Siika2D::UI()
{

	if (_instance == nullptr)
	{
		_instance = new Siika2D();

	}
	return _instance;

}


Siika2D::Siika2D()
{

}

Siika2D::~Siika2D()
{
	_instance = nullptr;

}



bool Siika2D::init(android_app* app)
{
	_application = app;
	_graphicsContext.init(app);
	_resourceManager.init(app->activity->assetManager);
}

void Siika2D::draw()
{
	//Here was a check if display existed

	// Just fill the screen with a color.
	glClearColor(0,1,0,1);
	glClear(GL_COLOR_BUFFER_BIT);

}
