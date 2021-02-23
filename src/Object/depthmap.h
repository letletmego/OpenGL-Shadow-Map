#ifndef _DEPTHMAP_H
#define _DEPTHMAP_H


#include "..\\OpenGL\\glbuffer.h"

#define CANVAS_DATA_ROW 6
#define CANVAS_DATA_COL 3

class CanvasData
{
public:
	static float _vertex[CANVAS_DATA_ROW * CANVAS_DATA_COL];
	static float _st[CANVAS_DATA_ROW * (CANVAS_DATA_COL - 1)];
};

class Canvas
{
public:
	static CanvasData _data;
	GLBuffer _vao;
	GLBuffer _vbo;
	unsigned int sampler;

public:
	~Canvas(void);
	Canvas(void);
	void BufferDataInitialize(void);
};


class DepthMap
{
public:
	unsigned int _width;
	unsigned int _height;
	unsigned int _fbo;
	unsigned int _texture_object;

public:
	~DepthMap(void);
	DepthMap(void);
	void Initialize(const unsigned int width, const unsigned int height);
};

#endif