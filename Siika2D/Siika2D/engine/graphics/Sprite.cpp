#include "Sprite.h"

using namespace graphics;

glm::vec2 * Sprite::getPositions()
{
	_positions[0].x = _position.x;
	_positions[0].y = _position.y;

	_positions[1].x = _position.x;
	_positions[1].y = _position.y - _origin.y;

	_positions[2].x = _position.x - _origin.x;
	_positions[2].y = _position.y - _origin.y;

	_positions[3].x = _position.x - _origin.x;
	_positions[3].y = _position.y;
	
	return _positions;
}
void Sprite::setPosition(glm::vec2 position)
{
	_position.x = position.x - _origin.x;
	_position.y = position.y - _origin.y;
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
	//Needs to change texPos
	float width = _textureUL.x - _textureLR.x;
	float height = _textureUL.y - _textureLR.y;
}