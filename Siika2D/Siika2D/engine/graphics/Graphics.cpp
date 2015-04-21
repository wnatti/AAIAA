#include "Graphics.h"

using namespace graphics;

Graphics::Graphics(android_app* application, core::ResourceManager* resourceManager) : GraphicsContext(application), TextureManager(resourceManager), SpriteManager(resourceManager)
{
	
}

void Graphics::clearGraphics()
{
	wipeContext();
	/*_indexBuffer.~Buffer();
	_vertexBuffer.~Buffer();*/

}

Graphics::~Graphics()
{

}