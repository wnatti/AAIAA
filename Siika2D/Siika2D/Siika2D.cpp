#include "Siika2D.h"

Siika2D* Siika2D::_instance = nullptr;

Siika2D* Siika2D::UI(android_app* app)
{

	if (_instance == nullptr)
	{
		_instance = new Siika2D(app);
	}
	return _instance;

}


Siika2D::Siika2D(android_app* app)
{
	LOGE("SIIKA CREATED");
	_exitRequested = false;
	//This is hella important
	_application = app;
	_application->userData = this;
	_application->onAppCmd = this->processCommands;

}

Siika2D::~Siika2D()
{
	
	_graphicsContext.wipeContext();
	//TODO: Release resources
	LOGE("SIIKA DESTROYED");
	_application = nullptr;
	_instance = nullptr;
}

bool Siika2D::init(android_app* app)
{

	_application = app;
	_application->userData = this;
	_application->onAppCmd = this->processCommands;

	if (app->savedState != nullptr)
	{
		// We are starting with a previous saved state; restore from it.
		_savedState = *(struct saved_state*)app->savedState;
	}

	if (_application != nullptr)
	{
		_resourceManager.init(_application->activity->assetManager);
	}
}

void Siika2D::processCommands(android_app* app,int32_t command)
{
	//Getting latest state
	saved_state *state = (saved_state*)app->userData;
	Siika2D* siikaInstance = Siika2D::UI(app);
	std::string cmdString = "APP_CMD_";
	switch (command)
	{
	case APP_CMD_START:
		cmdString += "START";
		LOGE(cmdString.c_str());
		siikaInstance->init(app);
		break;

	case APP_CMD_DESTROY:
		cmdString += "DESTROY";
		LOGE(cmdString.c_str());
		siikaInstance->_exitRequested = true;
		delete siikaInstance;
		break;

	case APP_CMD_SAVE_STATE:
		cmdString += "SAVE_STATE";
		LOGE(cmdString.c_str());
		//Creating state to restore from
		//malloc is recommended by native_app_glue
		app->savedState = malloc(sizeof(state));
		app->savedState = state;
		app->savedStateSize = sizeof(state);
		break;
	case APP_CMD_INIT_WINDOW:
		cmdString += "INIT_WINDOW";
		LOGE(cmdString.c_str());
		if (app->window != nullptr)
		{
			siikaInstance->_graphicsContext.init(app);
		}
		break;
	case APP_CMD_GAINED_FOCUS:
		cmdString += "GAINED_FOCUS";
		LOGE(cmdString.c_str());
		//TODO: go to input

		break;
	case APP_CMD_LOST_FOCUS:
		cmdString += "LOST_FOCUS";
		LOGE(cmdString.c_str());
		//TODO: go to input
		siikaInstance->draw();
		break;

	case APP_CMD_TERM_WINDOW:
		cmdString += "TERM_WINDOW";
		LOGE(cmdString.c_str());
		break;
	}
}


void Siika2D::draw()
{
	//Here was a check if display existed
	_graphicsContext.draw();
}
