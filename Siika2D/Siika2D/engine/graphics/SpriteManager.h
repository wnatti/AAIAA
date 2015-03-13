#pragma once
#include <vector>
#include "Sprite.h"
#include "Shader.h"
#include "BufferManager.h"
#include "ShaderManager.h"
#include <map>
<<<<<<< HEAD
#include "../glm/vec2.hpp"
#include "Texture.h"
=======
#include <algorithm>
>>>>>>> 6aaa3cf9cc670522b0831a8f6a5754d3a4575cfd

namespace graphics
{

	class SpriteManager
	{
	public:
		SpriteManager(ShaderManager * shdrMngr) :_shdrMngr(shdrMngr){};
<<<<<<< HEAD
		~SpriteManager();
		Sprite * createSprite();
		Sprite * createSprite(glm::vec2 location, glm::vec2 spriteSize, glm::vec2 spriteOrigin, Texture * texture, glm::vec2 textureUL, glm::vec2 textureLR);
=======
		~SpriteManager(){};
		Sprite * createSprite(){}
>>>>>>> 6aaa3cf9cc670522b0831a8f6a5754d3a4575cfd
		void drawSprites();
	private:
		Sprite * createSprite(Sprite * sprite);
		struct sprites_buffer
		{
			std::vector<Sprite*> sprites;
			BufferManager buffer;
		};
<<<<<<< HEAD

		void batchSprites(std::vector<Sprite*> *toBatch){};
		ShaderManager * _shdrMngr;
		std::map<Shader*, sprites_buffer*> _sprites;
=======
		
		void spriteBatcher(std::vector<Sprite> *toBatch);
		ShaderManager * _shdrMngr;
		std::map<Shader*, sprites_buffer> _sprites;
		/**
		Compares Z position between 2 sprites from the 'sprites' vector
		*/
		bool compareSpriteZs(Sprite &sprite1, Sprite &sprite2);
		/**
		Sorts sprites vector by comparing Z positions and textures
		*/
		vector<Sprite> *toBatch

>>>>>>> 6aaa3cf9cc670522b0831a8f6a5754d3a4575cfd
	};
}