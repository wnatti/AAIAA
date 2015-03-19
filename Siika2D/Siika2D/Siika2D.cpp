#include "Siika2D.h"

using namespace core;

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
	s2d_info("SIIKA CREATED");
}

Siika2D::~Siika2D()
{
	//GRAPHICS->
	//_graphicsContext.wipeContext();
	//TODO: Release resources

	s2d_info("SIIKA DESTROYED");
	_application = nullptr;
	_instance = nullptr;
}

void Siika2D::init(android_app* app)
{
	_drawReady = false;
	_application = app;
	_application->userData = this;
	_application->onAppCmd = this->processCommands;

	//Loading saved state if there is one
	if (app->savedState != nullptr)
		_savedState = *(struct saved_state*)app->savedState;
	_resourceManager.init(_application->activity->assetManager);

}

void Siika2D::initGraphics()
{
	_instance->GRAPHICS._graphicsContext.init(_instance->_application);
	_instance->_drawReady = true;

}

void Siika2D::releaseGraphics()
{
	_instance->GRAPHICS._graphicsContext.wipeContext();
	_instance->_drawReady = false;
}

void Siika2D::processCommands(android_app* app,int32_t command)
{
	//Getting latest state
	saved_state *state = (saved_state*)app->userData;
	std::string cmdString = "APP_CMD_";

	switch (command)
	{
	case APP_CMD_START:
		cmdString += "START";
		s2d_info(cmdString.c_str());
		//Application started,
		//initialize siika (get saved_state)
		_instance->init(app);
		break;

	case APP_CMD_DESTROY:
		cmdString += "DESTROY";
		s2d_info(cmdString.c_str());
		delete _instance;
		break;

	case APP_CMD_SAVE_STATE:
		cmdString += "SAVE_STATE";
		s2d_info(cmdString.c_str());
		//Creating state to restore from
		//malloc is recommended by native_app_glue
		app->savedState = malloc(sizeof(state));
		*((saved_state*)app->savedState) = *state;
		app->savedStateSize = sizeof(state);
		break;

	case APP_CMD_INIT_WINDOW:
		cmdString += "INIT_WINDOW";
		s2d_info(cmdString.c_str());
		_instance->initGraphics();
		break;

	case APP_CMD_GAINED_FOCUS:
		cmdString += "GAINED_FOCUS";
		s2d_info(cmdString.c_str());
		//TODO: go to input
		break;

	case APP_CMD_LOST_FOCUS:
		cmdString += "LOST_FOCUS";
		s2d_info(cmdString.c_str());
		//TODO: go to input
		//here was draw
		break;

	case APP_CMD_TERM_WINDOW:
		cmdString += "TERM_WINDOW";
		s2d_info(cmdString.c_str());
		_instance->releaseGraphics();
		break;

	case APP_CMD_LOW_MEMORY:
		cmdString += "LOW_MEMORY";
		s2d_info(cmdString.c_str());
		break;

	case APP_CMD_PAUSE:
		cmdString += "PAUSE";
		s2d_info(cmdString.c_str());
		break;

	case APP_CMD_STOP:
		cmdString += "STOP";
		s2d_info(cmdString.c_str());
		break;

	case APP_CMD_CONFIG_CHANGED:
		cmdString += "CONFIG_CHANGED";
		s2d_info(cmdString.c_str());
		break;

	}
}


void Siika2D::swap()
{
	GRAPHICS.swap();
}

void Siika2D::clear()
{
	GRAPHICS.clear();
}