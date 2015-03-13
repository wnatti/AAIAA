#include "SpriteManager.h"

using namespace graphics;



void SpriteManager::drawSprites()
{
	for(std::map<Shader*, sprites_buffer*>::iterator it = _sprites.begin(); it != _sprites.end(); it++)
	{

<<<<<<< HEAD
		batchSprites(&(*it->second).sprites);
=======
		spriteBatcher(&it->second.sprites);
>>>>>>> 6aaa3cf9cc670522b0831a8f6a5754d3a4575cfd
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
<<<<<<< HEAD
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
=======

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

>>>>>>> 6aaa3cf9cc670522b0831a8f6a5754d3a4575cfd
