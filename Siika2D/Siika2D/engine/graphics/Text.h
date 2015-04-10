#pragma once

#include "../core/ResourceManager.h"
#include "Buffer.h"

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace graphics
{
	class Text
	{
	public:
		Text(core::ResourceManager* resourceManager);
		~Text();

		void setFont(std::string filename);
		void setFontSize(GLint size);
		void setText(std::string text);
		void setPosition(GLfloat x, GLfloat y);
		void draw(glm::vec2 displaySize);

	private:
		void initFreetype();

		core::ResourceManager* _resourceManager;
		Buffer _buffer;
		std::string _text;
		GLint _size;
		glm::vec2 _position;
		FT_Face _fontFace;
		FT_Library _library;
	};
}
