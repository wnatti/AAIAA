#pragma once
#include <EGL/egl.h>
#include <GLES2\gl2.h>
#include "../core/ErrorHandler.h"

//#include "GL\glew.h"
#include <assert.h>
#include <string>
namespace graphics
{
	enum shdrAtrib { unknown = -1, position, color, texture };

	class Shader
	{
		friend class ShaderManager;
		/***
		Shader class includes fragment and vertex shaders. Uses default shader code if shader code is not provided in constructor.
		Default attribute names are Position: "position" Color: "color" TextureCoordinate: "texture"
		*/
	public:
		//const GLuint getColorAttr(){ return _colId; }
		//const GLuint getPositionAttr(){ return _posId; }
		//const GLuint getTextureAttr(){ return _texId; }
		const GLuint getProgram(){ return _program; }
		///calls glUseProgram() and enables shader attributes. This is for default shader only, also gets and enables default shader atributes
		void use();
	private:
		///Shader must be created using ShaderManager::createShader()
		Shader(bool color = false, bool texture = false);
		Shader(const GLchar * fragmentSource, const GLchar * vertexSource, bool color = false, bool texture = false);
		~Shader();
		void setColor(bool toSet){ _color = toSet; }
		void setTexture(bool toSet){ _texture = toSet; }


		bool compileShaders();
		bool linkProgram();
		void init();
		bool _default, _valid;
		std::string getProgramInfoLog(GLuint handle);
		std::string getShaderInfoLog(GLuint handle);
		bool _color, _texture;
		GLuint _fragHandle, _vertHandle;// , _colId, _posId, _texId;
		const GLchar * _fragSource;
		const GLchar * _vertSource;
		GLuint _program;
		//Default shader code
		//"attribute vec2 vertexUV;\n"
		GLchar * _posString = "position";
		GLchar * _colString = "color";
		GLchar * _texString = "texture";
		const GLchar* _defVertexSource =
			"attribute vec2 position;\n"
			"attribute vec4 color;\n"
			//"attribute vec2 texture;\n"

			//"uniform mat4 windowProjection;\n"
			//"uniform mat4 worldProjection;\n"
			//"uniform mat4 viewProjection;\n"

			//"varying vec2 UV;\n"
			"varying vec4 varyCol;\n"
			//"uniform sampler2D sampler;\n"
			"void main() {\n"
			//"	UV = texture;\n"
			"	varyCol = color; \n"
			"   gl_Position = vec4(position, 0, 1);\n"
			"}\n";
		// "   gl_Position = windowProjection * viewProjection * worldProjection * vec4(position, 0, 1);\n"
		const GLchar* _defFragmentSource =
			"varying lowp vec4 varyCol;\n"
			"void main()\n"
			"{\n"
			"   gl_FragColor = varyCol;\n"
			"}\n";
		//texture(sampler, UV) * varyCol; \n"
		//"   gl_FragColor = varyCol;\n"
	};
}