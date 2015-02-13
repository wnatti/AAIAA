#include "Shader.h"
using namespace graphics;

Shader::Shader():
_fragSource(_defFragmentSource), _vertSource(_defVertexSource)
{
	init();
}

Shader::Shader(const GLchar * fragmentSource, const GLchar * vertexSource) :
_fragSource(fragmentSource), _vertSource(vertexSource)
{
	init();
}

Shader::~Shader()
{}

std::string getShaderInfoLog(GLuint handle)
{
	GLint length;
	glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &length);
	GLchar * infoLog = new GLchar[length + 1];
	glGetShaderInfoLog(handle, length + 1, &length, infoLog);
	return std::string(infoLog);
}
std::string getProgramInfoLog(GLuint handle)
{
	GLint length;
	glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &length);
	GLchar * infoLog = new GLchar[length + 1];
	glGetProgramInfoLog(handle, length + 1, &length, infoLog);
	return std::string(infoLog);
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
		LOGE(getShaderInfoLog(_vertHandle));
		assert(status);
		return false;
	}
	glGetShaderiv(_fragHandle, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE)
	{
		LOGE(getShaderInfoLog(_vertHandle));
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
		LOGE(getProgramInfoLog(_vertHandle));
		//s2d_assert(status);
		assert(status);
		return false;
	}
}
bool Shader::use()
{
	glUseProgram(_program);
	_posId = glGetAttribLocation(_program, _posString);
	assert(_posId > -1);
	glEnableVertexAttribArray(_posId);
	_colId = glGetAttribLocation(_program, _colString);
	assert(_colId > -1);
	glEnableVertexAttribArray(_colId);
	_texId = glGetAttribLocation(_program, _texString);
	glEnableVertexAttribArray(_texId);
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