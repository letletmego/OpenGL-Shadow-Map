#ifndef _MATRIX_H
#define _MATRIX_H

class Mat4x4
{
public:
	float _m[16];

public:
	~Mat4x4(void);
	Mat4x4(void);

public:
	Mat4x4 operator * (const Mat4x4 &matrix) const;

	friend Mat4x4 Inverse(const Mat4x4 &matrix);
	friend Mat4x4 Transpose(const Mat4x4 &matrix);
	friend Mat4x4 Translation(float x, float y, float z);
	friend Mat4x4 Scaling(float x, float y, float z);
	friend Mat4x4 RotationX(float radian);
	friend Mat4x4 RotationY(float radian);
	friend Mat4x4 RotationZ(float radian);
};

class vec4f
{
public:
	float _x;
	float _y;
	float _z;
	float _w;

public:
	~vec4f(void);
	vec4f(void);
};

class color
{
public:
	float _b;
	float _g;
	float _r;

public:
	~color(void);
	color(void);
};

#endif