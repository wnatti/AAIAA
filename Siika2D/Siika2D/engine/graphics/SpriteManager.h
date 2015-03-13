#pragma once
#include <vector>
#include "Sprite.h"
#include "Shader.h"
#include "BufferManager.h"
#include "ShaderManager.h"
#include <map>
#include "../glm/vec2.hpp"
#include "Texture.h"

namespace graphics
{

	class SpriteManager
	{
	public:
		SpriteManager(ShaderManager * shdrMngr) :_shdrMngr(shdrMngr){};
		~SpriteManager();
		Sprite * createSprite();
		Sprite * createSprite(glm::vec2 location, glm::vec2 spriteSize, glm::vec2 spriteOrigin, Texture * texture, glm::vec2 textureUL, glm::vec2 textureLR);
		void drawSprites();
	private:
		Sprite * createSprite(Sprite * sprite);
		struct sprites_buffer
		{
			std::vector<Sprite*> sprites;
			BufferManager buffer;
		};

		void batchSprites(std::vector<Sprite*> *toBatch){};
		ShaderManager * _shdrMngr;
		std::map<Shader*, sprites_buffer*> _sprites;
	};
}