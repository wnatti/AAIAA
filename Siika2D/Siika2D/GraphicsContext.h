#pragma once
#include <jni.h>
#include <errno.h>
#include <EGL/egl.h>
#include <SDL.h>
#include <glm.hpp>
#include <GLES2\gl2.h>
#include <android/log.h>
#include "native_app_glue/android_native_app_glue.h"

class GraphicsContext
{
public:
	GraphicsContext();
	~GraphicsContext();
	void initialize();
private:

};