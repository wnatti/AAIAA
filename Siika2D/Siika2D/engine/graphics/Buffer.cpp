#include "Buffer.h"

using namespace graphics;

Buffer::Buffer()
{
	glGenBuffers(2, _buffers);
}


Buffer::~Buffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(2, _buffers);
}

void Buffer::bindVertexBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, _buffers[0]);
}

void Buffer::bindIndexBuffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[1]);
}


void Buffer::addVertices(GLfloat *vertices, int vertexCount, int stride)
{	
	if (vertexCount == 4)
		addRectIndices(vertexCount, stride);

	for (int i = 0; i < vertexCount*stride; i++)
	{
		_vertexData.push_back(vertices[i]);
	}
}

void Buffer::updateBufferData()
{
	glBindBuffer(GL_ARRAY_BUFFER, _buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, _vertexData.size() * sizeof(float), _vertexData.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexData.size() * sizeof(float), _indexData.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//Private
void Buffer::addRectIndices(int vertexCount, int stride)
{
	int index = _vertexData.size()/stride;

	GLuint INDEX_DATA[] = 
	{ 
		index, 
		index + 1,
		index + 2,
		index + 2,
		index + 3,
		index
	};

	for (int i = 0; i < vertexCount; i++)
	{
		_indexData.push_back(INDEX_DATA[i]);
	}
}