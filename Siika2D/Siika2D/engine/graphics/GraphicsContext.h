#pragma once

#include <EGL/egl.h>
#include <GLES2\gl2.h>
#include "../../native_app_glue/android_native_app_glue.h"
#include "../core/ErrorHandler.h"

/**
	Initializes the OpenGL ES 2.0 context
*/

class GraphicsContext
{

public:
	GraphicsContext(android_app* app);
	~GraphicsContext();
	void initialize();
	//TODO: tähän private: sitten kun engine class (Siika2D) on done  
	EGLDisplay _display;
	EGLint _width, _height, _format;
	EGLint _numConfig;
	EGLConfig _config;
	EGLSurface _surface;
	EGLContext _context;

};