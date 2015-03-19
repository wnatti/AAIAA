#include "Graphics.h"

using namespace graphics;

Graphics::Graphics()
{
	
}

void Graphics::clear()
{

}

void Graphics::swap()
{

}

void Graphics::initializeGraphics(core::ResourceManager *resourceManager)
{
	_shaderManager = new graphics::ShaderManager(resourceManager);
}
Graphics::~Graphics()
{
}