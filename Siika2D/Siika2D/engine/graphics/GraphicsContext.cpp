#include "GraphicsContext.h"


GraphicsContext::GraphicsContext()
{
}


GraphicsContext::~GraphicsContext()
{
}

void GraphicsContext::initialize(android_app* app)
{
	//Setting the color buffers' sizes etc.
	const EGLint attributes[] = {
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,
		EGL_NONE
	};

	//This gets us the display of the android device
	_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	bool result;

	//This initializes the display we just got
	result = eglInitialize(_display, 0, 0);
	s2d_assert(result);

	//This sets the configurations for the display
	result = eglChooseConfig(_display, attributes, &_config, 1, &_numConfig);
	s2d_assert(result);

	result = eglGetConfigAttrib(_display, _config, EGL_NATIVE_VISUAL_ID, &_format);
	s2d_assert(result);

	ANativeWindow_setBuffersGeometry(app->window, 0, 0,_format);

	_surface = eglCreateWindowSurface(_display, _config, app->window, NULL);
	_context = eglCreateContext(_display, _config, NULL, NULL);

	result = eglMakeCurrent(_display, _surface, _surface, _context);
	//s2d_assert(result, __FILE__, __LINE__);

	eglQuerySurface(_display, _surface, EGL_WIDTH, &_width);
	eglQuerySurface(_display, _surface, EGL_HEIGHT, &_height);

	glEnable(GL_CULL_FACE);

}
