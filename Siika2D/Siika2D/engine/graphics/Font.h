#pragma once

#include "TextureManager.h"
#include <ft2build.h>
#include FT_FREETYPE_H

namespace graphics
{
	class Font
	{
	public:
		Font(core::ResourceManager* resourceManager);
		~Font();

		void setFont(std::string filename);
		void setFontSize(GLint size);
		
	private:
		core::ResourceManager* _resourceManager;

		void initFreetype();
		FT_Face _fontFace;
		FT_Library _library;
	};
}