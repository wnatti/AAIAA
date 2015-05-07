#pragma once
#include <vector>
#include "Sprite.h"
#include "BufferManager.h"
#include "ShaderManager.h"
#include <map>
#include "../glm/vec2.hpp"
#include "Texture.h"
#include "ShaderManager.h"
#include "BufferManager.h"
#include <algorithm>

namespace core
{
	class Siika2D;
}

namespace graphics
{
	/**
		Class for managing sprites
	*/
	class SpriteManager
	{
		
		friend class core::Siika2D;

	public:
		SpriteManager(ShaderManager *shaderManager);
		~SpriteManager();
		Sprite * createSprite();
		Sprite * createSprite(glm::vec2 location, glm::vec2 spriteSize, glm::vec2 spriteOrigin, Texture * texture, glm::vec2 textureUL, glm::vec2 textureLR);
		Sprite * createSprite(Sprite * sprite);
		void drawSprites();
	protected:
	
		BufferManager * _bufferManager;
		std::vector<Sprite*> _sprites;

		ShaderManager* _shaderManager;
		//std::map<Shader*, sprites_buffer> _sprites;
		/**
		Compares Z position between 2 sprites from the 'sprites' vector
		*/
		bool compareSpriteZs(Sprite &sprite1, Sprite &sprite2);
		/**
		Sorts sprites vector by comparing Z positions and textures
		*/

	};
}