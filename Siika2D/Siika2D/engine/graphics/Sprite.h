#pragma once
#include "Texture.h"
#include "..\glm\vec2.hpp"

namespace graphics
{
	class Sprite
	{
	public:
		Sprite(){};
		~Sprite(){};
		void setTexture(Texture * TextureToSet){ _texture = TextureToSet; }
		GLfloat * getVertices();
		///Gets next sprite in spritesheet
		void step();
	private:
		Texture * _texture;
		glm::vec2 _origin, _size, _position, _texturePos;
		int _posZ;
	};
}