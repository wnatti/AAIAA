#pragma once
#include "Sprite.h"
#include "Buffer.h"
#include "ShaderManager.h"
#include <vector>

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