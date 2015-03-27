#pragma once

#include "TextureManager.h"

namespace graphics
{
	class Font
	{
	public:
		Font();
		~Font();
		void generateFont();

	private:
		core::ResourceManager* _resourceManager;
		std::vector<unsigned char> _fontBitmap;
		Texture* _fontTexture;

		void loadBitmap();

	};
}