#include "Sprite.h"

using namespace graphics;

GLfloat * Sprite::getVertices()
{
	glm::tvec2<GLfloat,glm::precision::defaultp> vertices[4];

	vertices[0].x = _position.x;
	vertices[0].y = _position.y;

	vertices[1].x = _position.x;
	vertices[1].y = _position.y-_origin.y;

	vertices[2].x = _position.x-_origin.x;
	vertices[2].y = _position.y-_origin.y;

	vertices[3].x = _position.x-_origin.x;
	vertices[3].y = _position.y;



	GLfloat * f;
	return f;
}