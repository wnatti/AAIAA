#pragma once
#include "Buffer.h"
#include "vec2.hpp"
#include "..\misc\Color.h"
#include <vector>

namespace graphics
{
	class BufferManager
	{
		friend class SpriteManager;

	public:
		BufferManager();
		~BufferManager();

		/**
			Creates vertex- and index-buffers
			from given parameters.
			Parameter-order must be followed.
		*/
		void setAttributes(GLint pos, GLint col, GLint textr);
		void addVertices(GLfloat* vertices, GLsizei size);
		void addIndices(GLint* indices, GLsizei size);
		void draw();
	private:
		std::vector<GLfloat> _vertices;
		std::vector<GLint> _indices;
		Buffer _indexBuffer;
		Buffer _vertexBuffer;
		GLint _positionId;
		GLint _colorId;
		GLint _textureId;
		GLsizei _strideLength;
		void addRectangle(glm::vec2* pos, glm::vec2* textr, Color* col);
	};
}