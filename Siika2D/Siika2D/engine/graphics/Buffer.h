#pragma once

#include <GLES2\gl2.h>
#include <cstdlib>

namespace graphics
{
	class Buffer;
}

class graphics::Buffer
{
public:


	Buffer();
	~Buffer();

	void addVertex();
	void addIndex();
	void fillVertexData(unsigned _size, void *_data);
	void unbindBuffer();
	void vertexAttributeBuffer(GLuint _vertex);



protected:
	GLuint _index;
	unsigned _size;


};

