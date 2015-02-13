#pragma once
#include "../core/MemoryManager.h"
#include <EGL/egl.h>
#include <GLES2\gl2.h>
#include "../core/ErrorHandler.h"
#include "../../native_app_glue/android_native_app_glue.h"
#include <assert.h>
#include <string>
namespace graphics
{
	class Shader
		/***
			Shader class includes fragment and vertex shaders. Uses default shader code if shader code is not provided in constructor.
			Default attribute names are Position: "position" Color: "color" TextureCoordinate: "texture"
		*/
	{
	public:
		Shader();
		Shader(const GLchar * fragmentSource, const GLchar * vertexSource);
		~Shader();
		bool compileShaders();
		bool linkProgram();
		const GLint getProgram(){ return _program; }
		///calls glUseProgram() and enables shader attributes
		bool use();
		const GLuint getColorAttrHndl(){ return _colId; }
		const GLuint getPositionAttrHndl(){ return _posId; }
		const GLuint getTextureAttrHndl(){ return _texId; }

	private:
		std::string getInfoLog(GLuint handle);
		GLuint _fragHandle, _vertHandle, _colId, _posId, _texId;
		const GLchar * _fragSource;
		const GLchar * _vertSource;
		GLuint _program;
		GLchar * _posString = "position";
		GLchar * _colString = "color";
		GLchar * _texString = "texture";
		void init();
		//Default shader code
		const GLchar* _defVertexSource =
			"attribute vec2 position;\n"
			"attribute vec4 color;\n"
			"varying vec4 varyCol;\n"
			"uniform mat4 windowProjection;\n"
			"uniform mat4 worldProjection;\n"
			"uniform mat4 viewProjection;\n"
			"void main() {\n"
			"	varyCol = color; \n"
			"   gl_Position = vec4(position, 0, 1);\n"
			"}\n";
		// "   gl_Position = windowProjection * viewProjection * worldProjection * vec4(position, 0, 1);\n"
		const GLchar* _defFragmentSource =
			"varying vec4 varyCol;\n"
			"void main() {\n"
			"   gl_FragColor = varyCol;\n"
			"}\n";
	};
}