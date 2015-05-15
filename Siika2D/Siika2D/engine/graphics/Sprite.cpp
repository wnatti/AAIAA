#include "Sprite.h"

using namespace graphics;

glm::vec2 * Sprite::getBounds(glm::vec2 pos)
{
	
	_bounds[0].x = pos.x - _origin.x;
	_bounds[0].y = pos.y - _origin.y;

	_bounds[1].x = pos.x - _origin.x;
	_bounds[1].y = pos.y - _origin.y + _size.y;

	_bounds[2].x = pos.x - _origin.x + _size.x;
	_bounds[2].y = pos.y - _origin.y + _size.y;

	_bounds[3].x = pos.x - _origin.x + _size.x;
	_bounds[3].y = pos.y - _origin.y;

	return _bounds;
}


glm::vec2 * Sprite::getPositions()
{
	rotate();
/*
	_positions[0].x = _position.x - _origin.x;
	_positions[0].y = _position.y - _origin.y;

	_positions[1].x = _position.x - _origin.x;
	_positions[1].y = _position.y - _origin.y + _size.y;

	_positions[2].x = _position.x - _origin.x + _size.x;
	_positions[2].y = _position.y - _origin.y + _size.y;

	_positions[3].x = _position.x - _origin.x + _size.x;
	_positions[3].y = _position.y - _origin.y;
*/

	return _positions;
}
void Sprite::setPosition(glm::vec2 position)
{
	_position.x = position.x;// -_origin.x;
	_position.y = position.y;// -_origin.y;
}
void Sprite::rotate()
{

	glm::vec2 posAtZero[4];
	getBounds(glm::vec2(0, 0));

	for (int i = 0; i < 4; i++)
		posAtZero[i] = _bounds[i];

	glm::vec2 pos[4];
	getBounds(_position);

	for (int i = 0; i < 4; i++)
		pos[i] = _bounds[i];
	
	if (_rotationAngle > 360.f)
		_rotationAngle -= 360.f;
	else if (_rotationAngle < -360.f)
		_rotationAngle += 360.f;

	//_rotationAngle = -glm::radians(_rotationAngle);

	glm::mat4 rotationMatrix = glm::rotate(glm::radians(_rotationAngle), glm::vec3(0, 0, 1));
		/*
		glm::mat4(glm::cos(_rotationAngle), glm::sin(_rotationAngle), 0.f, 0.f,
		-glm::sin(_rotationAngle), glm::cos(_rotationAngle), 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
		*/
	glm::vec2 difference;
	float x, y;
	for (int i = 0; i < 4; i++)
	{
		
		glm::vec4 tempPos = rotationMatrix*glm::vec4(posAtZero[i], 0.f, 1.f);
		difference = posAtZero[i] - glm::vec2(tempPos.x, tempPos.y);
		x = -difference.x;
		y = -difference.y;
		_positions[i].x = pos[i].x + x;
		_positions[i].y = pos[i].y + y;
		//_positions[i] = pos[i] + difference; // (posAtZero[i] - glm::vec2(tempPos.x, tempPos.y));
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
	float width = _textureLR.x - _textureUL.x;
	float height = _textureLR.y - _textureUL.y;


	//Needs to change horizontal position
	if((_textureLR.x + width) < 1.0f)
	{
		_textureUL.x += width;
		_textureLR.x += width;

	}
	else
	{
		//_textureUL.y = 0;
		//_textureUL.x = 0;
		//_textureLR.y = height;
		//_textureLR.x = width;
		
		//Needs to change vertical position
		if(_textureLR.y + height < 1.0f)
		{
			_textureUL.y += height;
			_textureUL.x = 0;
			_textureLR.y += height*2;
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