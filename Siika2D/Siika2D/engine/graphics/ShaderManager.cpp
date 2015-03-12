#include "ShaderManager.h"
using namespace graphics;

/*
Käyttäjä antaa atribuutin nimen bindaa sen ja
antaa sen indeksin shaderille
*/
void ShaderManager::setAtrib(shdrAtrib atrib, GLint value)
{	
	for(int i = 0; i < 3; i++)
	{
		if(_atrib[i].atr == atrib)
		{
			_atrib[i].indx = value;
			return;
		}
	}
	for(int i = 0; i < 3; i++)
	{
		if(_atrib[i].indx == -1)
		{
			_atrib[i].atr = atrib;
			_atrib[i].indx = value;
			return;
		}
	}
	return;
}

void ShaderManager::setAtribs(GLint pos, GLint tex, GLint col)
{
	_atrib[0].atr = position;
	_atrib[0].indx = pos;

	_atrib[0].atr = color;
	_atrib[0].indx = col;

	_atrib[0].atr = texture;
	_atrib[0].indx = tex;
	return;
}
GLint ShaderManager::findAtrib(shdrAtrib atribToFind)
{
	for(int i = 0; i < 3; i++)
	{
		if(_atrib[i].atr == atribToFind)
			return _atrib[i].indx;
	}
	return -1;
}
void ShaderManager::useShader(void)
{
	if(_currentShader)
	{
		GLint pos = findAtrib(position);
		GLint tex = findAtrib(texture);
		GLint col = findAtrib(color);
		_currentShader->use(pos,col,tex);
	}
	else
	{
		//Gets default shader
		if(defaultIndx == -1)
		{
			_currentShader = new Shader();
			_shaders.push_back(_currentShader);
			defaultIndx = _shaders.size()-1;
		}
		else  //should never come here
		{
			//s2d_error("No current shader but default shader loaded: ShaderManager::useShader()");
			_currentShader = _shaders[defaultIndx];
		}
	}
	//s2d_assert(_currentShader);
	assert(_currentShader);
	_currentShader->use();
}
Shader * ShaderManager::createShader(char * vertPath, char * fragPath)
{ 
	std::string * fragSource;
	std::string * vertSource;

	core::ResourceManager rmngr;
	vertSource = rmngr.loadTextFile(vertPath);
	fragSource = rmngr.loadTextFile(fragPath);

	Shader * newShdr = findShader(vertSource->c_str(), fragSource->c_str());
	if(!newShdr)
	{
		newShdr = new Shader(fragSource->c_str(), vertSource->c_str());
		if(newShdr->_valid)
			_shaders.push_back(newShdr); 
		else // Compile or link failed infolog in logcat
		{
			delete newShdr;
			newShdr = nullptr;
		}
	}
	_currentShader = newShdr;
	return _currentShader; 
}
Shader * ShaderManager::findShader(const char * vertSource, const char * fragSource)
{
	for(std::vector<Shader*>::iterator it = _shaders.begin(); it != _shaders.end(); it++)
	{
		Shader * shdr = *it;
		if(strcmp(shdr->_vertSource,vertSource) == 0)
		{
			if(strcmp(shdr->_fragSource, fragSource) == 0)
				return shdr;
		}
	}
	return nullptr;
}
GLint ShaderManager::enableShaderAtribute(char * atribName)
{
	GLint id = glGetAttribLocation(_currentShader->_program, atribName);
	assert(id > -1);
	glEnableVertexAttribArray(id);
	return id;
}
GLint ShaderManager::enableShaderAtribute(char * atribName, shdrAtrib atribType)
{
	GLint id = glGetAttribLocation(_currentShader->_program, atribName);
	assert(id > -1);
	glEnableVertexAttribArray(id);
	setAtrib(atribType, id);
	return id;
}