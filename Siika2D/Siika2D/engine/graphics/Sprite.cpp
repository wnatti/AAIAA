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

	return _positions;
}
void Sprite::setPosition(glm::vec2 position)
{
	_position.x = position.x;// -_origin.x;
	_position.y = position.y;// -_origin.y;
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

Sprite* Sprite::create(glm::vec2 position, glm::vec2 size, glm::vec2 origin)
{
	Sprite *sprite = new Sprite(position, size, origin);
}

void Sprite::draw()
{
	_bufferManager->addRectangle(getPositions(), getTexturePos(), getColor());
	glBindTexture(GL_TEXTURE_2D,_texture->getTexture());
	_bufferManager->draw();
	glBindTexture(GL_TEXTURE_2D, 0u);


}