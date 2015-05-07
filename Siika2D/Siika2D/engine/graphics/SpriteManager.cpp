#include "SpriteManager.h"
#
using namespace graphics;



void SpriteManager::drawSprites()
{
	GLint err = glGetError();
	s2d_assert(err == 0);

		err = glGetError();
		s2d_assert(err == 0);

		_shaderManager->useShader(true, true);

		err = glGetError();
		s2d_assert(err == 0);
		
		for(std::vector<Sprite*>::iterator sit = _sprites.begin(); sit != _sprites.end(); sit++)
		{
			(*sit)->draw();
		}

		_shaderManager->getShader()->use(false);
}

Sprite * SpriteManager::createSprite()
{
	return createSprite(nullptr);
}
SpriteManager::SpriteManager(ShaderManager *shaderManager)
{
	_shaderManager = shaderManager;
}
SpriteManager::~SpriteManager()
{


}
Sprite * SpriteManager::createSprite(Sprite * sprite)
{
	return sprite;
}

Sprite * SpriteManager::createSprite(glm::vec2 location, glm::vec2 spriteSize, glm::vec2 spriteOrigin, Texture * texture, glm::vec2 textureUL, glm::vec2 textureLR)
{
	Sprite * sprt = new Sprite(location, spriteSize, spriteOrigin, texture, textureUL, textureLR);
	_sprites.push_back(sprt);
	return sprt;
}

bool SpriteManager::compareSpriteZs(Sprite &sprite1, Sprite &sprite2)
{
	if (sprite1._posZ > sprite2._posZ)
		return true;
	else
		return false;
}