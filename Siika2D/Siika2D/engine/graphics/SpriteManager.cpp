#include "SpriteManager.h"

using namespace graphics;



void SpriteManager::drawSprites()
{
	GLint err = glGetError();
	for(std::map<Shader*, sprites_buffer*>::iterator it = _sprites.begin(); it != _sprites.end(); it++)
	{
		
		it->first->use(); // shader->use()
		// TODO: Check for changes before recreating buffer
		//BufferManager buf = (*it->second).buffer;
		BufferManager buf;
		buf.setAttributes(position, color, unknown);
		Sprite * sprt = *(*it->second).sprites.begin();
		for(std::vector<Sprite*>::iterator sit = (*it->second).sprites.begin(); sit != (*it->second).sprites.end(); sit++)
		{
			//spriteBatcher((*sit));
			glm::vec2 * positions = (*sit)->getPositions();
			glm::vec2 * textures = (*sit)->getTexturePos();
			//graphics::Color * col = (*sit)->getColor();
			buf.addRectangle(positions, nullptr, sprt->getColor());
			//buf.addRectangle(positions, textures,nullptr);
		}
		; //First sprite
		//glActiveTexture(GL_TEXTURE0);
		err = glGetError();
		//glBindTexture(GL_TEXTURE_2D, sprt->_texture->getTexture());
		err = glGetError();
		buf.draw();
		err = glGetError();
		//glBindTexture(GL_TEXTURE_2D, 0u);
		//glActiveTexture(0u);
//		it->first->use(false);
	}
}
Sprite * SpriteManager::createSprite()
{
	return createSprite(nullptr);
}
SpriteManager::SpriteManager(ShaderManager * shdrMngr):_shdrMngr(shdrMngr)
{
	int size = _sprites.size();
}

Sprite * SpriteManager::createSprite(Sprite * sprite)
{
	
	Shader * shdr = _shdrMngr->getShader();
	if(!sprite)
		sprite = new Sprite();
	sprites_buffer * bfr;
	if(_sprites.size() != 0)
		for(std::map<Shader*, sprites_buffer*>::iterator it = _sprites.begin(); it != _sprites.end(); it++)
		{
			if(it->first == shdr) // Sprites with this shader already exist
			{
				(*it->second).sprites.push_back(sprite);
				return sprite;
			}
		}
	bfr = new sprites_buffer;
	//bfr->buffer.setAttributes(position, unknown, texture);
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

/*
SpriteManager::~SpriteManager()
{
	for(std::map<Shader*, sprites_buffer*>::iterator it = _sprites.begin(); it != _sprites.end(); it++)
	{
		(*it->second).sprites.empty();
	}

}
*/

bool SpriteManager::compareSpriteZs(Sprite &sprite1, Sprite &sprite2)
{
	if (sprite1._posZ > sprite2._posZ)
		return true;
	else
		return false;
}


void SpriteManager::spriteBatcher(std::vector<Sprite> *toBatch)
{
	int i, j;
	

	for ( i = 0; i < toBatch->size(); i++)
	{
		for (j = i + 1; j < toBatch->size(); j++)
		{
			if (!compareSpriteZs(toBatch->at(i), toBatch->at(j)))
			{
					Sprite temp = toBatch->at(j);
					toBatch->at(j) = toBatch->at(i);
					toBatch->at(i) = temp;
			}
		}
	}

	for (i = 0; i < toBatch->size(); i++)
	{
		for (j = i + 1; j < toBatch->size(); j++)
		{
			if (toBatch->at(i)._posZ == toBatch->at(j)._posZ)
			{
				if (toBatch->at(i)._texture->getTexture() < toBatch->at(j)._texture->getTexture())
				{
						Sprite temp = toBatch->at(j);
						toBatch->at(j) = toBatch->at(i);
						toBatch->at(i) = temp;
				}
			}
		}
	}

}