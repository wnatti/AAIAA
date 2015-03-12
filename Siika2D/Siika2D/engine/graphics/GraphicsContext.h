#pragma once

#include <EGL/egl.h>
#include <GLES2\gl2.h>
#include "../../native_app_glue/android_native_app_glue.h"
#include "../core/ErrorHandler.h"

/**
	Initializes OpenGL ES 2.0 context
		and wipes it when needed
*/

namespace graphics
{

	class GraphicsContext
	{

	public:
		GraphicsContext();
		~GraphicsContext();
	

		/**
			glClear and swapBuffers		
		*/
		void draw();
		/**
			Initializes OpenGL ES 2.0 context
		*/
		void init(android_app* app);

		/**
			Clears the context
		*/
		void wipeContext();

		void clear();

		void swap();

	private:

		EGLDisplay _display;
		EGLint _width, _height, _format;
		EGLint _numConfig;
		EGLConfig _config;
		EGLSurface _surface;
		EGLContext _context;

	};
};