#include "Shader.h"
using namespace graphics;

Shader::Shader()
{
	default = true;
	init();
	_fragSource = _defFragmentSource;
	_vertSource = _defVertexSource;
	valid = compileShaders();
	if(valid)
		valid = linkProgram();
	//valid = true if neither complie or link returned false
}

Shader::Shader(const GLchar * fragmentSource, const GLchar * vertexSource) :
_fragSource(fragmentSource), _vertSource(vertexSource)
{
	default = false;
	init();
	valid = compileShaders();
	if(valid)
		valid = linkProgram();
	//valid = true if neither complie or link returned false
}

Shader::~Shader()
{
	
}

std::string Shader::getShaderInfoLog(GLuint handle)
{
	GLint length;
	glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &length);
	GLchar * infoLog = new GLchar[length + 1];
	glGetShaderInfoLog(handle, length + 1, &length, infoLog);
	std::string log;
	log.append(infoLog);
	delete infoLog;
	return log;
}
std::string Shader::getProgramInfoLog(GLuint handle)
{
	GLint length;
	glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &length);
	GLchar * infoLog = new GLchar[length + 1];
	glGetProgramInfoLog(handle, length + 1, &length, infoLog);
	std::string log;
	log.copy(infoLog, length);
	delete infoLog;
	return log;
}
bool Shader::compileShaders()
{
	GLint status;
	_program = glCreateProgram();
	_vertHandle = glCreateShader(GL_VERTEX_SHADER);
	_fragHandle = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_vertHandle, 1, &_vertSource, NULL);
	glShaderSource(_fragHandle, 1, &_fragSource, NULL);
	glCompileShader(_vertHandle);
	glCompileShader(_fragHandle);
	glGetShaderiv(_vertHandle, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE)
	{
		std::string infoLog = getShaderInfoLog(_vertHandle);
		//LOGE("Vertex shader complile failed \n" << getShaderInfoLog(_vertHandle));
		assert(status);
		return false;
	}
	glGetShaderiv(_fragHandle, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE)
	{
		std::string infoLog = getShaderInfoLog(_fragHandle);
		//LOGE("Fragment shader complie failed \n" << getShaderInfoLog(_fragHandle));
		assert(status);
		return false;
	}
	glAttachShader(_program, _vertHandle);
	glAttachShader(_program, _fragHandle);
	return true;
}
bool Shader::linkProgram()
{
	GLint status;
	glLinkProgram(_program);
	glGetProgramiv(_program, GL_LINK_STATUS, &status);
	if(status == GL_FALSE)
	{
		//LOGE("Linking program failed \n" << getProgramInfoLog(_program));
		//s2d_assert(status);
		assert(status);
		return false;
	}
	return true;
}
void Shader::use(GLint posId, GLint colId, GLint textureId)
{
	glUseProgram(_program);
}
void Shader::use()
{
	glUseProgram(_program);
	_posId = glGetAttribLocation(_program, _posString);
	assert(_posId < -1);
	glEnableVertexAttribArray(_posId);
	_colId = glGetAttribLocation(_program, _colString);
	assert(_colId < -1);
	glEnableVertexAttribArray(_colId);
	_texId = glGetAttribLocation(_program, _texString);
	glEnableVertexAttribArray(_texId);
	return;
}

void Shader::init()
{
	_colId = -1;
	_posId = -1;
	_texId = -1;
	_program = -1;
	_fragHandle = -1;
	_vertHandle = -1;
}