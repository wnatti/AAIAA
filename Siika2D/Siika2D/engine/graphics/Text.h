#pragma once

#include "../core/ErrorHandler.h"
#include "SpriteManager.h"
#include "Font.h"

namespace graphics
{
	class Text
	{

	public:
		Text(SpriteManager* spriteManager);
		~Text();

	private:
		SpriteManager* _spriteManager;
		Sprite* charSprite;

	};
}
