#pragma once
#include <vector>
#include "Shader.h"
#include "Sprite.h"
#include "Buffer.h"

namespace graphics
{
	class SpriteManager
	{
	public:
		SpriteManager();
		~SpriteManager();
		void drawSprites();
	private:
		void batchSprites();
		Shader _shaderToUse;
		std::vector<Sprite> _sprites;
		Buffer _spriteBuffer;
	};

	SpriteManager::SpriteManager()
	{
	}

	SpriteManager::~SpriteManager()
	{
	}
}