#include "Font.h"

using namespace graphics;

Font::Font(core::ResourceManager* resourceManager)
{
	_resourceManager = resourceManager;
	initFreetype();
}

Font::~Font()
{

}

void Font::setFont(std::string filename)
{
	std::vector<unsigned char>* fontData =_resourceManager->loadFile(filename);
	int error = FT_New_Memory_Face(_library, fontData->data(), sizeof(unsigned char)*fontData->size(), 0, &_fontFace);
	s2d_assert(error == 0);
}

void Font::setFontSize(GLint size)
{
	int error = FT_Set_Pixel_Sizes(_fontFace, size, size);
	s2d_assert(error == 0);
}

void Font::initFreetype()
{
	int error = FT_Init_FreeType(&_library);
	s2d_assert(error == 0);
}