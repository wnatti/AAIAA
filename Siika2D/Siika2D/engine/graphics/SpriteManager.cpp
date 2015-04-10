#include "SpriteManager.h"
#
using namespace graphics;



void SpriteManager::drawSprites()
{
	GLint err = glGetError();
	std::vector<GLfloat> vertices;
	std::vector<GLint> indecis;
	int spriteCount = 0;
	//GLfloat vertices[16]; // Pos Tex

	for(std::map<Shader*, sprites_buffer*>::iterator it = _sprites.begin(); it != _sprites.end(); it++)
	{
		
		//it->first->use(); // shader->use()
		// TODO: Check for changes before recreating buffer
		//BufferManager buf = (*it->second).buffer;
		//BufferManager buf;
		//buf.setAttributes(position, color, unknown);
		//_shdrMngr->useShader(false,true);
		//_bfr->setAttributes(position, unknown, texture);
		Sprite * sprt = *(*it->second).sprites.begin();
		for(std::vector<Sprite*>::iterator sit = (*it->second).sprites.begin(); sit != (*it->second).sprites.end(); sit++)
		{
			//spriteBatcher((*sit));
			glm::vec2 * positions = (*sit)->getPositions();
			glm::vec2 * textures = (*sit)->getTexturePos();
			for(int i = 0; i <= 3; i++)
			{
				vertices.push_back(positions[i].x);
				vertices.push_back(positions[i].y);

				vertices.push_back(positions[i].x);
				vertices.push_back(positions[i].y);

				//vertices.push_back(textures[i].x);
				//vertices.push_back(textures[i].y);

				//vertices.push_back(1.0f);
				//vertices.push_back(0.0f);
				//vertices.push_back(0.0f);
				//vertices.push_back(1.0f);
			}
			indecis.push_back(1);
			indecis.push_back(2);
			indecis.push_back(4);
			indecis.push_back(2);
			indecis.push_back(3);
			indecis.push_back(4);
			//graphics::Color * col = (*sit)->getColor();
			//buf.addRectangle(positions, nullptr, sprt->getColor());
			//buf.addRectangle(positions, nullptr, new Color(255,0,0,255));
			//buf.addRectangle(positions, textures,nullptr);
			_bfr->addVertices(vertices.data(), sizeof(GLfloat) * 16);// 24);
			_bfr->addIndices(indecis.data(), sizeof(GLint) * 6);

		}
		//First sprite
		
		err = glGetError();
		glBindTexture(GL_TEXTURE_2D, sprt->_texture->getTexture());
		//glActiveTexture(GL_TEXTURE0);
		err = glGetError();
		_bfr->draw();
		//buf.draw();
		err = glGetError();
		bool check = false;
		//glBindTexture(GL_TEXTURE_2D, 0u);
		//glActiveTexture(0u);
//		it->first->use(false);
	}
}
Sprite * SpriteManager::createSprite()
{
	return createSprite(nullptr);
}
SpriteManager::SpriteManager(ShaderManager * shdrMngr, BufferManager * bfr) :_shdrMngr(shdrMngr), _bfr(bfr)
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