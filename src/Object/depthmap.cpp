#include "depthmap.h"
#include <gl\\glew.h>


float CanvasData::_vertex[] = 
{
	-1.0f, -1.0f, 0.0f,   1.0f, 1.0f, 0.0f,  1.0f, -1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f,  -1.0f, 1.0f, 0.0f,  1.0f,  1.0f, 0.0f
};

float CanvasData::_st[] = 
{
	0.0f, 0.0f,  1.0f, 1.0f,  1.0f, 0.0f,
	0.0f, 0.0f,  0.0f, 1.0f,  1.0f, 1.0f
};


Canvas::~Canvas(void)
{
}

Canvas::Canvas(void)
	: _vao()
	, _vbo()
{
}

void Canvas::BufferDataInitialize(void)
{
	_vao.Initialize(1);
	_vbo.Initialize(2);

	glGenVertexArrays(_vao.N_Buffer(), _vao.BufferPointer());
	glGenBuffers(_vbo.N_Buffer(), _vbo.BufferPointer());

	glBindVertexArray(_vao[0]);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * CANVAS_DATA_ROW * CANVAS_DATA_COL, _data._vertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * CANVAS_DATA_ROW * CANVAS_DATA_COL, _data._st, GL_STATIC_DRAW);

	glBindVertexArray(0);

	return;
}

DepthMap::~DepthMap(void)
{
}

DepthMap::DepthMap(void)
	: _width(0)
	, _height(0)
	, _fbo(0)
	, _texture_object(0)
{
}

void DepthMap::Initialize(const unsigned int width, const unsigned int height)
{
	_width = width;
	_height = height;

	// Create a texture object for depth map
	glGenTextures(1, &_texture_object);
	glBindTexture(GL_TEXTURE_2D, _texture_object);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _width, _height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// Set up wrapping modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Generate the framebuffer name
	glGenFramebuffers(1, &_fbo);
	// Create the framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _texture_object, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return;
}