#ifndef _CUBE_H
#define _CUBE_H


#include "..\\OpenGL\\glbuffer.h"

#define CUBE_DATA_COL 3
#define CUBE_DATA_ROW 36

class CubeData1
{
public:
	static float _vertex[CUBE_DATA_ROW * CUBE_DATA_COL];
	static float _normal[CUBE_DATA_ROW * CUBE_DATA_COL];
	static float _color[CUBE_DATA_ROW * CUBE_DATA_COL];
	static float _st[CUBE_DATA_ROW * (CUBE_DATA_COL - 1)];
};

class CubeData2
{
public:
	static float _vertex[CUBE_DATA_ROW * CUBE_DATA_COL];
	static float _normal[CUBE_DATA_ROW * CUBE_DATA_COL];
	static float _color[CUBE_DATA_ROW * CUBE_DATA_COL];
	static float _st[CUBE_DATA_ROW * (CUBE_DATA_COL - 1)];
};


class Cube1
{
public:
	static CubeData1 _data;
	GLBuffer _vao;
	GLBuffer _vbo;

public:
	~Cube1(void);
	Cube1(void);
	void BufferDataInitialize(void);
};

class Cube2
{
public:
	static CubeData2 _data;
	GLBuffer _vao;
	GLBuffer _vbo;

public:
	~Cube2(void);
	Cube2(void);
	void BufferDataInitialize(void);
};

#endif