#include "plane.h"


float PlaneData::_vertex[] = 
{
	-6.0, -1.0, 6.0,   6.0, -1.0, -6.0,  6.0, -1.0,  6.0,
	-6.0, -1.0, 6.0,  -6.0, -1.0, -6.0,  6.0, -1.0, -6.0
};

float PlaneData::_normal[] = 
{
	0.0,  1.0,  0.0,   0.0,  1.0,  0.0,   0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,   0.0,  1.0,  0.0,   0.0,  1.0,  0.0
};

float PlaneData::_color[] = 
{
	1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
};

float PlaneData::_st[] = 
{
	0.0, 0.0,  1.0, 1.0,  1.0, 0.0,
	0.0, 0.0,  0.0, 1.0,  1.0, 1.0,
};

//-----------------------------------------------------------------

Plane::~Plane(void)
{
	glDeleteBuffers(_vbo.N_Buffer(), _vbo.BufferPointer());
	glDeleteVertexArrays(_vao.N_Buffer(), _vao.BufferPointer());
}

Plane::Plane(void)
{
}

void Plane::BufferDataInitialize(void)
{
	_vao.Initialize(1);
	_vbo.Initialize(3);

	glGenVertexArrays(_vao.N_Buffer(), _vao.BufferPointer());
	glGenBuffers(_vbo.N_Buffer(), _vbo.BufferPointer());

	glBindVertexArray(_vao[0]);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * PLANE_DATA_ROW * PLANE_DATA_COL, _data._vertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * PLANE_DATA_ROW * PLANE_DATA_COL, _data._normal, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * PLANE_DATA_ROW * PLANE_DATA_COL, _data._color, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return;
}