#pragma once
#include "Texture.h"

namespace graphics
{
	class Sprite
	{
	public:
		Sprite();
		~Sprite();
		void setTexture(Texture * TextureToSet){ _texture = TextureToSet; }
		GLfloat * getVertices();
		///Gets next sprite in spritesheet
		void step();
	private:
		Texture * _texture;
		int _width, _height,
		_posX, _posY, _posZ,
		_originX, _originY;

		float _texX, _texY;


	};

	Sprite::Sprite()
	{
	}

	Sprite::~Sprite()
	{
	}
}