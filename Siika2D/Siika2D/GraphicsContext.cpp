#include "GraphicsContext.h"


GraphicsContext::GraphicsContext()
{
}


GraphicsContext::~GraphicsContext()
{
}

void GraphicsContext::initialize()
{
	const EGLint attributes[] = {
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,
		EGL_NONE
	};

	EGLint width, height, dummy, format;
	EGLint numConfigs;
	EGLConfig configurations;
	EGLSurface surface;
	EGLContext context;

	EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	s2d_assert(eglInitialize(display, 0, 0),__FILE__,__LINE__);

	eglChooseConfig(display, attributes, &configurations, 1, &numConfigs);

}
