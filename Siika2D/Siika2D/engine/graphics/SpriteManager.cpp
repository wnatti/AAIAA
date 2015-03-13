#include "SpriteManager.h"

using namespace graphics;

void SpriteManager::drawSprites()
{
	for(std::map<Shader*, sprites_buffer*>::iterator it = _sprites.begin(); it != _sprites.end(); it++)
	{

		batchSprites(&(*it->second).sprites);
		it->first->use(); // shader->use()
		// TODO: Check for changes before recreating buffer
		BufferManager buf = (*it->second).buffer;
	
		for(std::vector<Sprite*>::iterator sit = (*it->second).sprites.begin(); sit != (*it->second).sprites.end(); sit++)
		{
			glm::vec2 * positions = (*sit)->getPositions();
			glm::vec2 * textures = (*sit)->getTexturePos();
			graphics::Color * col = (*sit)->getColor();
			buf.addRectangle(positions, textures,col);
		}
		//buf.bindIndexBuffer();
		//buf.bindVertexBuffer();
		buf.draw();
		glUseProgram(0u);
	}
}
Sprite * SpriteManager::createSprite()
{
	return createSprite(nullptr);
}
Sprite * SpriteManager::createSprite(Sprite * sprite)
{
	Shader * shdr; //= _shdrMngr->getShader();
	if(!sprite)
		sprite = new Sprite();
	sprites_buffer * bfr;
	for(std::map<Shader*, sprites_buffer*>::iterator it = _sprites.begin(); it != _sprites.end(); it++)
	{
		if(it->first == shdr) // Sprites with this shader already exist
		{
			(*it->second).sprites.push_back(sprite);
			return sprite;
		}
	}
	bfr = new sprites_buffer;
	bfr->sprites.push_back(sprite);
	_sprites.insert(std::pair<Shader*, sprites_buffer*>(shdr, bfr));
	return sprite;
}

Sprite * SpriteManager::createSprite(glm::vec2 location, glm::vec2 spriteSize, glm::vec2 spriteOrigin, Texture * texture, glm::vec2 textureUL, glm::vec2 textureLR)
{
	Sprite * sprt = new Sprite(location, spriteSize, spriteOrigin, texture, textureUL, textureLR);
	createSprite(sprt);
	return sprt;
}

SpriteManager::~SpriteManager()
{
	for(std::map<Shader*, sprites_buffer*>::iterator it = _sprites.begin(); it != _sprites.end(); it++)
	{
		(*it->second).sprites.empty();
	}

}