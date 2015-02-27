#include "SpriteManager.h"

using namespace graphics;

void SpriteManager::drawSprites()
{
	for(std::map<Shader*, sprites_buffer>::iterator it = _sprites.begin(); it != _sprites.end(); it++)
	{

		batchSprites(&it->second.sprites);
		it->first->use(); // shader->use()
		Buffer buf = it->second.buffer;
	
		for(std::vector<Sprite>::iterator sit = it->second.sprites.begin(); sit != it->second.sprites.end(); sit++)
		{
			GLfloat * vertices = sit->getVertices();
			buf.addVertices(vertices);
		}
		buf.bindIndexBuffer();
		buf.bindVertexBuffer();
		//buf.draw();
	}
}