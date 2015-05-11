#pragma once
#include "Texture.h"
#include "..\glm\vec2.hpp"
#include "glm.hpp"
#include "..\misc\color.h"
#include <gtx/transform.hpp>

namespace graphics
{
	class Sprite
	{
		friend class SpriteManager;
	public:

		void setTexture(Texture * TextureToSet, glm::vec2 textureUpperLeft, glm::vec2 textureLowerRigth){ _texture = TextureToSet; }
		void setPosition(glm::vec2 position);
		void setSize(glm::vec2 size){ _size = size; }
		void setOrigin(glm::vec2 origin){ _origin = origin; }
		void setColor(Color col)
		{ 
			if(!_col)
				_col = new Color(0,0,0,0);
			_col->setRGBA(col.getR(), col.getG(), col.getB(), col.getA()); 
		}
		void setRotation(GLfloat angle){ _rotationAngle = angle; }
		void setZ(int Z){ _posZ = Z; }
		const glm::vec2 * getPosition(){ return &_position; }
		Color * getColor(){ return _col; };


		///Gets next sprite in spritesheet
		void step();
	protected:
		Sprite(){};
		Sprite(glm::vec2 position, glm::vec2 size, glm::vec2 origin) :
			_position(position), _size(size), _origin(origin), _texture(nullptr), _col(nullptr), _rotationAngle(0){};

		Sprite(glm::vec2 position, glm::vec2 size, glm::vec2 origin, Texture * TextureToSet, glm::vec2 textureUpperLeft, glm::vec2 textureLowerRigth) :
			_position(position), _size(size), _origin(origin), _texture(TextureToSet), _textureUL(textureUpperLeft), _textureLR(textureLowerRigth), _col(nullptr), _rotationAngle(0){};
		~Sprite()
		{
			delete _col;
		};
	private:
		glm::vec2 * getBounds(glm::vec2 pos);
		glm::vec2 _bounds[4];
		glm::vec2 * getPositions();
		glm::vec2 * getTexturePos();
		void rotate();
		Texture * _texture;
		glm::vec2 _origin, _size, _position;
		glm::vec2 _textureUL, _textureLR; // upperLeft, lowerRight
		int _posZ;
		GLfloat _rotationAngle;
		glm::vec2 _positions[4];
		glm::vec2 _texPos[4];
		Color * _col;
		bool _draw;
		void moveSprite();
	};
}