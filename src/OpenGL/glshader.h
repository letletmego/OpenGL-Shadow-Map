#ifndef _GL_SHADER
#define _GL_SHADER


#include <vector>
#include <gl\\glew.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")


class String
{
private:
	char *_buffer;
	size_t _buffer_size;

public:
	~String(void);
	String(void);
	String(char *str);

	void operator = (const char *str);
	operator char * (void);
};

//---------------------------------------------------------------

class GLShader
{
public:
	unsigned int _program;

private:
	unsigned int _n_shader;
	unsigned int *_shader;
	std::vector<String *> _variable;

public:
	~GLShader(void);
	GLShader(void);

public:
	friend char *LoadShader(const char *shader_file);
	friend unsigned int CompileShader(char *shader_file_name, GLenum shader_type, char *debug_file_name);
	friend unsigned int LinkShader(const GLuint *shader, int n_shader, char *debug_file_name);

public:
	void Initialize(unsigned int n_shader);
	void AddVariable(char *variable);
	const char *GetVariable(unsigned int index);
	void CompileVertexShader(char *shader_file_name, char *debug_file_name);
	void CompileFragmentShader(char *shader_file_name, char *debug_file_name);
	void LinkShader(char *debug_file_name);


};

#endif