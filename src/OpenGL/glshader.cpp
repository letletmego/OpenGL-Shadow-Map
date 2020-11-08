#include "glshader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


String::~String(void)
{
	if (_buffer)
	{
		free(_buffer);
		_buffer = 0x00;
		_buffer_size = 0;
	}
}

String::String(void)
	: _buffer(0x00)
	, _buffer_size(0)
{
}

String::String(char *str)
	: _buffer(0x00)
	, _buffer_size(0)
{
	*this = str;
}

void String::operator = (const char *str)
{
	if (_buffer)
	{
		free(_buffer);
		_buffer_size = 0;
	}

	for (int idx = 0; ; ++idx)
	{
		++_buffer_size;

		if (*(str + idx) == '\0')
			break;
	}

	_buffer = (char *)malloc(_buffer_size);
	memset(_buffer, 0, _buffer_size);
	memcpy(_buffer, str, _buffer_size);

	return;
}

String::operator char * (void)
{
	return _buffer;
}

//---------------------------------------------------------------

GLShader::~GLShader(void)
{
	for (int idx = 0; idx < _variable.size(); ++idx)
	{
		delete _variable[idx];
	}

	glDeleteProgram(_program);

	if (_shader != 0x00)
	{
		free(_shader);
		_shader = 0x00;
	}
}

GLShader::GLShader(void)
	: _program(0)
	, _n_shader(0)
	, _shader(0x00)
{
}

char *LoadShader(const char *file_name)
{
	if (file_name == 0x00)
		return 0x00;

	FILE *file_ptr = fopen(file_name,"rt");
	if (file_ptr == 0x00)
		return 0x00;

	char* shader_file = 0x00;
	int count = 0;
	
	fseek(file_ptr, 0, SEEK_END);
	count = ftell(file_ptr);
	rewind(file_ptr);

	if (count == 0)
	{
		fclose(file_ptr);
		return 0x00;
	}

	shader_file = (char *)malloc(sizeof(char) * (count + 1));
	count = fread(shader_file, sizeof(char), count, file_ptr);
	shader_file[count] = '\0';

	fclose(file_ptr);

	return shader_file;
}

unsigned int CompileShader(char* shader_file_name, GLenum shader_type, char* debug_file_name)
{
	FILE *shader_debug = fopen(debug_file_name, "a");

	char *shader_file = LoadShader(shader_file_name);
	unsigned int shader = glCreateShader(shader_type);

	// Check shader file load successfully or not 
	if(shader_file == 0x00)
	{
		fprintf(shader_debug, "%s : %s\n", shader_file_name, "Fail to load shader");
		return 0;
	}

	glShaderSource(shader, 1, (const GLchar**)&shader_file, 0x00);
	glCompileShader(shader);

	// Check Shader
	GLint status = GL_FALSE;
	GLint info_log_length = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
	
	char *shader_error_message = (char *)malloc(sizeof(char) * (info_log_length + 1));
	if (info_log_length > 0)
	{
		glGetShaderInfoLog(shader, info_log_length, NULL, shader_error_message);
		fprintf(shader_debug, "%s :\n\n", shader_file_name);
		fprintf(shader_debug, "%s\n", shader_error_message);
	}

	free(shader_error_message);
	fclose(shader_debug);

	return shader;
}

unsigned int LinkShader(const GLuint *shader, int n_shader, char *debug_file_name)
{
	FILE *shader_debug = fopen(debug_file_name, "a");

	GLuint program = glCreateProgram();
	for (int idx = 0; idx < n_shader; ++idx)
	{
		glAttachShader(program, *(shader + idx));
	}

	glLinkProgram(program);

	// Check Link Program 
	GLint status = GL_FALSE;
	GLint info_log_length = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);

	char *shafer_program_error_Message = (char *)malloc(sizeof(char) * (info_log_length + 1));
	if (info_log_length > 0)
	{
		glGetProgramInfoLog(program, info_log_length, NULL, shafer_program_error_Message);
		fprintf(shader_debug, "%s\n", shafer_program_error_Message);
	}

	free(shafer_program_error_Message);
	fclose(shader_debug);

	return program;
}

void GLShader::Initialize(unsigned int n_shader)
{
	if (_shader != 0x00)
		return;

	_n_shader = n_shader;
	_shader = (unsigned int *)malloc(sizeof(unsigned int) * n_shader);

	return;
}

void GLShader::AddVariable(char *variable)
{
	_variable.push_back(new String(variable));

	return;
}

const char *GLShader::GetVariable(unsigned int index)
{
	if (index >= _variable.size())
		return 0x00;

	return *_variable[index];
}

void GLShader::CompileVertexShader(char *shader_file_name, char *debug_file_name)
{
	_shader[0] = ::CompileShader(shader_file_name, GL_VERTEX_SHADER, debug_file_name);

	return;
}

void GLShader::CompileFragmentShader(char *shader_file_name, char *debug_file_name)
{
	_shader[1] = ::CompileShader(shader_file_name, GL_FRAGMENT_SHADER, debug_file_name);

	return;
}

void GLShader::LinkShader(char *debug_file_name)
{
	_program = ::LinkShader(_shader, _n_shader, debug_file_name);

	return;
}