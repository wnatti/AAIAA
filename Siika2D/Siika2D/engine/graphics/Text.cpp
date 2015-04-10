#include "Text.h"

using namespace graphics;

Text::Text(core::ResourceManager* resourceManager) :_buffer(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW)
{
	_resourceManager = resourceManager;

	setPosition(0, 0);
	_size = 18;

	initFreetype();
}


Text::~Text()
{

}


void Text::setFont(std::string filename)
{
	std::vector<unsigned char>* fontData = _resourceManager->loadFile(filename);
	int error = FT_New_Memory_Face(_library, fontData->data(), sizeof(unsigned char)*fontData->size(), 0, &_fontFace);
	s2d_assert(error == 0);

	setFontSize(_size);
}


void Text::setFontSize(GLint size)
{
	_size = size;
	int error = FT_Set_Pixel_Sizes(_fontFace, _size, _size);
	s2d_assert(error == 0);
}


void Text::setText(std::string text)
{
	_text = text;
}


void Text::setPosition(GLfloat x, GLfloat y)
{
	_position = glm::vec2(x, y);
}


void Text::draw(glm::vec2 displaySize)
{
	_buffer.bindBuffer();

	const char* pointerToText;

	FT_GlyphSlot glyph = _fontFace->glyph;

	float x = _position.x;
	float y = _position.y;
	float scaleX = 2.0 / displaySize.x;
	float scaleY = 2.0 / displaySize.y;


	for (pointerToText = _text.c_str(); *pointerToText; pointerToText++) {
		if (FT_Load_Char(_fontFace, *pointerToText, FT_LOAD_RENDER))
			continue;

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_ALPHA,
			glyph->bitmap.width,
			glyph->bitmap.rows,
			0,
			GL_ALPHA,
			GL_UNSIGNED_BYTE,
			glyph->bitmap.buffer
			);

		float x2 = x + glyph->bitmap_left * scaleX;
		float y2 = -y - glyph->bitmap_top * scaleY;
		float w = glyph->bitmap.width * scaleX;
		float h = glyph->bitmap.rows * scaleY;

		GLfloat box[4][4] = {
			{ x2, -y2, 0, 0 },
			{ x2 + w, -y2, 1, 0 },
			{ x2, -y2 - h, 0, 1 },
			{ x2 + w, -y2 - h, 1, 1 },
		};

		_buffer.setBufferData(box, sizeof(box));
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		x += (glyph->advance.x >> 6) * scaleX;
		y += (glyph->advance.y >> 6) * scaleY;
	}

	_buffer.unbindBuffer();
}


void Text::initFreetype()
{
	int error = FT_Init_FreeType(&_library);
	s2d_assert(error == 0);
}

