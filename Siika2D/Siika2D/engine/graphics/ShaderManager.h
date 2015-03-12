#pragma once
#include "Shader.h"

#include "../core/ErrorHandler.h"
#include "../core/ResourceManager.h"

#include <EGL/egl.h>
#include <GLES2\gl2.h>
#include <vector>
#include <map>
//#include "../../Siika2D.h"

//#include "GL\glew.h"

namespace graphics
{

	enum shdrAtrib { unknown = -1, position, color, texture };
	
	class ShaderManager
	{
		/***
			Class for managing and loading shaders
			Default values for shader attributes are: "position", "color", "texture" 
			and they will be used unless new values are set with either setAtrib or setAtribs

			To use default shader 
			1) call useShader()
			
			To use custom shaders 
			1) call createShader(vertexshaderPath, fragmentShaderPath)
			2) enable shader atributes with enableShaderAtribute
			3) set shader atributes with setAtrib(s)
			4) call useShader()


		*/
	public:
		
		ShaderManager():_currentShader(nullptr),defaultIndx(-1){};
		~ShaderManager(){ _shaders.empty(); }
		///Sets all shader attributes existing values will be overwritten
		void setAtribs(GLint position, GLint texture, GLint color);

		///Used to enable specific shader atribute returns atribute handle
		GLint enableShaderAtribute(char * atribName);

		///Sets and enables specified atribute
		GLint enableShaderAtribute(char * atribName,shdrAtrib atribType);

		///Sets single given shader attribute value
		void setAtrib(shdrAtrib atribToSet, GLint value);
		
		/**
			Loads shader code with resourceManager. 
			If shader attribute values are not set default ones will be used. 
			Returns nullptr if compliling or linking fails infolog in logcat
		*/
		Shader * createShader(char * vertPath, char * fragPath);
		
		///Compiles shaders links program for _currentShader if its not set uses default shaders
		void useShader(void);

		///Sets the shader to be used by useShader()
		void setCurrentShader(Shader * shaderToUse){ _currentShader = shaderToUse; }
	private:
		//Finds already created shader in _shaders
		Shader * findShader(const char * vertSource, const char * fragSource);
		GLint findAtrib(shdrAtrib atribToFind);

		int defaultIndx;
		Shader * _currentShader;
		struct s_shdrAtrib
		{
			shdrAtrib atr = unknown;
			GLint indx = -1;
		};

		s_shdrAtrib _atrib[3];
		std::vector<Shader*> _shaders;
		std::map<shdrAtrib, char*> _shaderAtribs;
	};
}