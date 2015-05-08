#include "Sprite.h"

using namespace graphics;

glm::vec2 * Sprite::getPositions()
{
	_positions[0].x = _position.x - _origin.x;
	_positions[0].y = _position.y - _origin.y;

	_positions[1].x = _position.x - _origin.x;
	_positions[1].y = _position.y - _origin.y + _size.y;

	_positions[2].x = _position.x - _origin.x + _size.x;
	_positions[2].y = _position.y - _origin.y + _size.y;

	_positions[3].x = _position.x - _origin.x + _size.x;
	_positions[3].y = _position.y - _origin.y;

	rotate();

	return _positions;
}
void Sprite::setPosition(glm::vec2 position)
{
	_position.x = position.x;// -_origin.x;
	_position.y = position.y;// -_origin.y;
}
void Sprite::rotate()
{
	if (_rotationAngle > 360.f)
		_rotationAngle -= 360.f;
	else if (_rotationAngle < -360.f)
		_rotationAngle += 360.f;

	_rotationAngle = glm::radians(_rotationAngle);

	glm::mat4 rotationMatrix =
		glm::mat4(glm::cos(_rotationAngle), glm::sin(_rotationAngle), 0.f, 0.f,
		-glm::sin(_rotationAngle), glm::cos(_rotationAngle), 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);

	for (int i = 0; i < 4; i++)
	{
		glm::vec4 tempPos = rotationMatrix*glm::vec4(_positions[i], 0.f, 1.f);
		_positions[i] = glm::vec2(tempPos.x, tempPos.y);
	}
}
glm::vec2 * Sprite::getTexturePos()
{
	
	_texPos[0] = _textureUL;
	_texPos[1].x = _textureUL.x;
	_texPos[1].y = _textureLR.y;

	_texPos[2] = _textureLR;
	_texPos[3].x = _textureLR.x;
	_texPos[3].y = _textureUL.y;
	return _texPos;
}
void Sprite::step()
{
	///TODO: is y change in right direction ?
	float width = _textureUL.x - _textureLR.x;
	float height = _textureUL.y - _textureLR.y;


	//Needs to change horizontal position
	if(_textureLR.x + width < 1.0f)
	{
		_textureUL.x += width;
		_textureLR.x += width;

	}
	else
	{
		//Needs to change vertical position
		if(_textureLR.y + height < 1.0f)
		{
			_textureUL.y += height;
			_textureUL.x = 0;
			_textureLR.y += height;
			_textureLR.x = width;
		}
		else//Go to first frame
		{
			_textureUL.y = 0;
			_textureUL.x = 0;
			_textureLR.y = height;
			_textureLR.x = width;
		}
	}
}