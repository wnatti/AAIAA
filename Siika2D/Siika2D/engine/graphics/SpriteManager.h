#pragma once
#include <vector>
#include "Sprite.h"
#include "Shader.h"
#include "Buffer.h"
#include "ShaderManager.h"
#include <map>

namespace graphics
{

	class SpriteManager
	{
	public:
		SpriteManager(ShaderManager * shdrMngr) :_shdrMngr(shdrMngr){};
		~SpriteManager(){};
		Sprite * createSprite(){};
		void drawSprites();
	private:
		struct sprites_buffer
		{
			std::vector<Sprite> sprites;
			Buffer buffer;
		};
		void batchSprites(std::vector<Sprite> * toBatch){};
		ShaderManager * _shdrMngr;
		std::map<Shader*, sprites_buffer> _sprites;
	};
}