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
	
	
		/**
			Clears the context thoroughly
		*/
		void wipeContext();
		/**
			Clears the screen with a color (default green)
		*/
		void clear();
		/**
			Swap buffers
		*/
		void swap();


	protected:

		/**
			Initializes OpenGL ES 2.0 context
		*/


		GraphicsContext(android_app *app);
		~GraphicsContext();

		void init(android_app* app);

		EGLDisplay _display;
		EGLint _windowWidth, _windowHeight, _format, _numConfig;
		EGLConfig _config;
		EGLSurface _surface;
		EGLContext _context;

	};
}