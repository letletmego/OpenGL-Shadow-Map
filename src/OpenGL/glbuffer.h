#ifndef _GL_BUFFER
#define _GL_BUFFER


#include <gl\\glew.h>

class GLBuffer
{
private:
	unsigned int _n_buffer;
	unsigned int *_buffer;

public:
	~GLBuffer(void);
	GLBuffer(void);

	void Initialize(unsigned int n_buffer);
	unsigned int N_Buffer(void) const;
	unsigned int operator [] (const int &index) const;
	unsigned int *BufferPointer(void) const;
};


inline void UniformMat4x4(GLuint *shader_program, const char *shader_variable, GLfloat *matrix, GLenum GL)
{
	GLuint uniform_location = 0;
	
	uniform_location = glGetUniformLocation(*shader_program, shader_variable);

	glUniformMatrix4fv(uniform_location, 1, GL, matrix);
	
	return;
}

inline void Uniform3fv(GLuint *shader_program, const char *shader_variable, GLfloat *float3, GLenum GL)
{
	GLuint uniform_location = 0;
	
	uniform_location = glGetUniformLocation(*shader_program, shader_variable);

	glUniform3fv(uniform_location, 1, float3);

	return;
}

inline void GLSLSampler(GLuint *shader_program, const char *shader_variable, GLint texture_unit)
{
	GLuint uniform_location = 0;

	uniform_location = glGetUniformLocation(*shader_program, shader_variable);

	glUniform1i(uniform_location, texture_unit);

	return;
}

#endif