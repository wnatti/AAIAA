#include "SpriteManager.h"

using namespace graphics;



void SpriteManager::drawSprites()
{
	for(std::map<Shader*, sprites_buffer>::iterator it = _sprites.begin(); it != _sprites.end(); it++)
	{

		spriteBatcher(&it->second.sprites);
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
				if (toBatch->at(i)._texture.getTexture() < toBatch->at(j)._texture.getTexture())
				{
						Sprite temp = toBatch->at(j);
						toBatch->at(j) = toBatch->at(i);
						toBatch->at(i) = temp;
				}
			}
		}
	}

}

