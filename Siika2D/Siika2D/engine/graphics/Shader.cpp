#include "Shader.h"
using namespace graphics;

Shader::Shader()
{
	_default = true;
	init();
	_fragSource = _defFragmentSource;
	_vertSource = _defVertexSource;
	_valid = compileShaders();
	if(_valid)
		_valid = linkProgram();
	//valid = true if neither complie or link returned false
}

Shader::Shader(const GLchar * fragmentSource, const GLchar * vertexSource) :
_fragSource(fragmentSource), _vertSource(vertexSource)
{
	_default = false;
	init();
	_valid = compileShaders();
	if(_valid)
		_valid = linkProgram();
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
		//s2d_error("Vertex shader complile failed \n" << getShaderInfoLog(_vertHandle));
		s2d_assert(status);
		return false;
	}

	glGetShaderiv(_fragHandle, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE)
	{
		std::string infoLog = getShaderInfoLog(_fragHandle);
		s2d_error("Fragment shader compile failed \n");
		s2d_assert(status);
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
		//s2d_error("Linking program failed \n" << getProgramInfoLog(_program));
		//s2d_s2d_assert(status);
		s2d_assert(status);
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
	s2d_assert(_posId < -1);
	glEnableVertexAttribArray(_posId);
	_colId = glGetAttribLocation(_program, _colString);
	s2d_assert(_colId < -1);
	glEnableVertexAttribArray(_colId);
	//_texId = glGetAttribLocation(_program, _texString);
	//s2d_assert(_colId < -1);
	//glEnableVertexAttribArray(_texId);5
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