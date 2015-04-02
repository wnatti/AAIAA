#include "Buffer.h"

using namespace graphics;

Buffer::Buffer(GLenum bufferType, GLenum usagePattern)
{
	int err = glGetError();
	glGenBuffers(1, &_buffer);
	err = glGetError();
	s2d_assert(err == 0);

	_bufferType = bufferType;
	_usagePattern = usagePattern;
}

Buffer::~Buffer()
{
	glBindBuffer(_bufferType, 0);
	glDeleteBuffers(1, &_buffer);
}

void Buffer::bindBuffer()
{
	glBindBuffer(_bufferType, _buffer);
	GLint err = glGetError();
	s2d_assert(err == 0);
}

void Buffer::unbindBuffer()
{
	glBindBuffer(_bufferType, 0);
	GLint err = glGetError();
	s2d_assert(err == 0);
}

void Buffer::subBufferData(void* bufferData, GLsizei size, GLint offset)
{
	glBindBuffer(_bufferType, _buffer);
	glBufferSubData(_bufferType, offset, size, bufferData);
	s2d_assert(glGetError() == 0);

	glBindBuffer(_bufferType, 0);
}


void Buffer::setBufferData(void* bufferData, GLsizei size)
{
	
	glBindBuffer(_bufferType, _buffer);
	int err = glGetError();
	s2d_assert(err == 0);
	glBufferData(_bufferType, size, bufferData, _usagePattern);
	err = glGetError();
	s2d_assert(err == 0);

	glBindBuffer(_bufferType, 0);
}