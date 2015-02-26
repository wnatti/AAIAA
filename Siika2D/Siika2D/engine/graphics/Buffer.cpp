#include "Buffer.h"

using namespace graphics;

Buffer::Buffer(GLenum bufferType, GLenum usagePattern)
{
	glGenBuffers(1, _buffers);
	s2d_assert(glGetError == 0);

	_bufferType = bufferType;
	_usagePattern = usagePattern;
}


Buffer::~Buffer()
{
	glBindBuffer(_bufferType, 0);
	glDeleteBuffers(1, _buffers);
}

void Buffer::bindBuffer()
{
	glBindBuffer(_bufferType, _buffers[0]);
	s2d_assert(glGetError == 0);
}

void Buffer::unbindBuffer()
{
	glBindBuffer(_bufferType, 0);
	s2d_assert(glGetError == 0);
}

void Buffer::addBufferData(void* bufferData, GLsizei size, GLint offset)
{
	glBindBuffer(_bufferType, _buffers[0]);
	glBufferSubData(_bufferType, offset, size, bufferData);
	s2d_assert(glGetError == 0);

	glBindBuffer(_bufferType, 0);
}


void Buffer::setBufferData(void* bufferData, GLsizei size)
{
	glBindBuffer(_bufferType, _buffers[0]);
	glBufferData(_bufferType, size, bufferData, _usagePattern);
	s2d_assert(glGetError == 0);

	glBindBuffer(_bufferType, 0);
}