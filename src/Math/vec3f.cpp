#include "vec3f.h"


vec3f::~vec3f(void)
{
}

vec3f::vec3f(void)
	: _x(0.0f)
	, _y(0.0f)
	, _z(0.0f)
{
}

vec3f::vec3f(const float &value)
	: _x(value)
	, _y(value)
	, _z(value)
{
}

vec3f::vec3f(const float &x, const float &y, const float &z)
	: _x(x)
	, _y(y)
	, _z(z)
{
} 

vec3f vec3f::operator + (const vec3f &vector) const
{
	return vec3f(_x + vector._x, _y + vector._y, _z + vector._z);
}

vec3f vec3f::operator - (const vec3f &vector) const
{
	return vec3f(_x - vector._x, _y - vector._y, _z - vector._z);
}

vec3f vec3f::operator - (void) const
{
	return vec3f(-_x, -_y, -_z);
}

vec3f vec3f::operator * (const float &scalar) const
{
	return vec3f(_x * scalar, _y * scalar, _z * scalar);
}

float vec3f::operator [] (const int &index) const
{
	if (index == 0)
		return _x;
	if (index == 1)
		return _y;
	if (index == 2)
		return _z;

	return 0.0f;
}