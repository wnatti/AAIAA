#pragma once

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <vector>

#include"../core/ErrorHandler.h"

namespace graphics
{
	class Texture;
}

class graphics::Texture
{
public:
	Texture(int width, int height, std::vector<unsigned char> imageData);
	~Texture();

	GLuint getTexture();

private:
	int _width, _height;
	GLuint _texture;
	std::vector<unsigned char> _imageData;
	void initialize();
};
