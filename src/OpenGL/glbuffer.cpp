#include "glbuffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


GLBuffer::~GLBuffer(void)
{
	if (_buffer != 0x00)
	{
		free(_buffer);
		_buffer = 0x00;
	}
}

GLBuffer::GLBuffer(void)
	: _n_buffer(0)
	, _buffer(0x00)
{
}

void GLBuffer::Initialize(unsigned int n_buffer)
{
	if (_buffer != 0x00)
		return;

	_n_buffer = n_buffer;

	_buffer = (unsigned int *)malloc(sizeof(unsigned int) * _n_buffer);
	memset(_buffer, 0, sizeof(unsigned int) * _n_buffer);

	return;
}

unsigned int GLBuffer::N_Buffer(void) const
{
	return _n_buffer;
}

unsigned int GLBuffer::operator [] (const int &index) const
{
	if (_buffer == 0x00)
		return 0;

	if (index >= _n_buffer)
		return 0;

	return _buffer[index];
}

unsigned int *GLBuffer::BufferPointer(void) const
{
	return _buffer;
}
