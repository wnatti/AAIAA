#include "Graphics.h"

using namespace graphics;

Graphics::Graphics(android_app* application, core::ResourceManager* resourceManager) : GraphicsContext(application), ShaderManager(resourceManager)
{
	
}

Graphics::~Graphics()
{
}