#include "Texture.h"

namespace graphics
{
	Texture::Texture(int width, int height, std::vector<unsigned char> imageData)
	{
		_width = width;
		_height = height;
		_imageData = imageData;

		initialize();
	}

	Texture::~Texture()
	{

	}

	void Texture::initialize()
	{
		glGenTextures(1, &_texture);
	}

	GLuint Texture::getTexture()
	{
		return _texture;
	}
}