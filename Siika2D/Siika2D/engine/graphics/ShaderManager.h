#pragma once
#include "Shader.h"

#include "../core/ErrorHandler.h"
#include "../core/ResourceManager.h"

#include <EGL/egl.h>
#include <GLES2\gl2.h>
#include <vector>
#include <map>



namespace graphics
{

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
			2) call useShader()

			If colors or textures are needed use shader::setColor and shader::setTexture

		*/
	public:
		

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
	protected:
		ShaderManager(core::ResourceManager * resMngr) :_rmngr(resMngr), _currentShader(nullptr), _defaultIndx(-1){
			s2d_info("SHADER MANAGER CREATED");

		};
		~ShaderManager(){ _shaders.empty(); }
		//Finds already created shader in _shaders
		Shader * findShader(const char * vertSource, const char * fragSource);

		int _defaultIndx;
		Shader * _currentShader;
		
		std::vector<Shader*> _shaders;
		std::map<shdrAtrib, char*> _shaderAtribs;
		core::ResourceManager * _rmngr;
	};
}