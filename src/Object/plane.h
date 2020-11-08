#ifndef _PLANE_H
#define _PLANE_H


#include "..\\OpenGL\\glbuffer.h"

#define PLANE_DATA_COL 3
#define PLANE_DATA_ROW 6

class PlaneData
{
public:
	static float _vertex[PLANE_DATA_ROW * PLANE_DATA_COL];
	static float _normal[PLANE_DATA_ROW * PLANE_DATA_COL];
	static float _color[PLANE_DATA_ROW * PLANE_DATA_COL];
	static float _st[PLANE_DATA_ROW * (PLANE_DATA_COL - 1)];
};

//-----------------------------------------------------------------

class Plane
{
public:
	static PlaneData _data;
	GLBuffer _vao;
	GLBuffer _vbo;

public:
	~Plane(void);
	Plane(void);
	void BufferDataInitialize(void);
};

#endif