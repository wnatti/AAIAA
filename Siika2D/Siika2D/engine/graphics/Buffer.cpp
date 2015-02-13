#include "Buffer.h"

namespace graphics
{
	Buffer::Buffer()
	{
	}


	Buffer::~Buffer()
	{
		
	}

	void Buffer::addVertex()
	{

		glGenBuffers(1, &_index);
		glBindBuffer(GL_ARRAY_BUFFER, _index);
		glBufferData(GL_ARRAY_BUFFER, _size * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

	}

	void Buffer::addIndex()
	{
		glGenBuffers(1, &_index);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _size * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
	}

	void Buffer::fillVertexData(unsigned _size, void *_data)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _index);
		glBufferSubData(GL_ARRAY_BUFFER, 0, _size, _data);

	}

	void Buffer::vertexAttributeBuffer(GLuint _vertex)
	{
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, _vertex);
		glVertexAttribPointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			0
		);

	}

}