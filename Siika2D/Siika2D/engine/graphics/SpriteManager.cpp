#include "SpriteManager.h"

using namespace graphics;

void SpriteManager::drawSprites()
{
	batchSprites();

	for(std::vector<Sprite>::iterator it = _sprites.begin(); it != _sprites.end(); it++)
	{
		_spriteBuffer.addVertices(it->getVertices());
	}
	_spriteBuffer.bindIndexBuffer();
	_spriteBuffer.bindVertexBuffer();
	_spriteBuffer.updateBufferData();
	_shaderToUse.use();	//Uses default shader need TODO: use shadermanager;

	glVertexAttribPointer(_shaderToUse.getPositionAttr(), 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
	glVertexAttribPointer(_shaderToUse.getTextureAttr(), 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(2));
	glVertexAttribPointer(_shaderToUse.getColorAttr(), 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(4));
	glDrawElements(GL_TRIANGLES, _sprites.size() * 6, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(0));
	//UnbindBuffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);
	glUseProgram(0u);
	//Swap buffers?
}

void SpriteManager::batchSprites()
{

}