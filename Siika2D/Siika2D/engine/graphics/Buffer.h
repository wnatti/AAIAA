#pragma once

#include <GLES2\gl2.h>
#include <cstdlib>
#include <vector>


namespace graphics
{
	/**
		Buffers for drawn vertices and indices.
	*/
	class Buffer
	{
	public:

		/**
			Constructor.
			Generate buffer names and set stride values.
		*/
		Buffer();

		/**
			Destructor.
			Unbind and delete all buffers.
		*/
		~Buffer();

		/**
			Bind vertex buffer object.
		*/
		void bindVertexBuffer();

		/**
			Bind index buffer object.
		*/
		void bindIndexBuffer();

		/**
			Add vertices to vertex buffer for drawing.
		*/
		void addVertices(GLfloat *vertices, int vertexCount = 4, int stride = 8);

		/**
			Give vertex and index data buffer's data store.
			Call before drawing.
		*/
		void updateBufferData();

	private:
		
		//Fill index buffer for rectangle shapes
		void addRectIndices(int vertexCount, int stride);

		GLuint *_buffers;
		std::vector<GLfloat> _vertexData;
		std::vector<GLint> _indexData;
	};
}