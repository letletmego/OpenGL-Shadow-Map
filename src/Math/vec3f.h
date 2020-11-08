#ifndef _VEC3F_H
#define _VEC3F_H

#include <math.h>

#define PI       3.14159265358979323846

class vec3f
{
public:
	struct
	{
		float _x;
		float _y;
		float _z;
	};
	
public:
	~vec3f(void);
	vec3f(void);
	vec3f(const float &value);
	vec3f(const float &x, const float &y, const float &z);

public:
	vec3f operator + (const vec3f &vector) const;
	vec3f operator - (const vec3f &vector) const;
	vec3f operator - (void) const;
	vec3f operator * (const float &scalar) const;
	float operator [] (const int &index) const;
};


inline float Length(const vec3f &vector)
{
	return sqrt(vector._x * vector._x + vector._y * vector._y + vector._z * vector._z);
}

inline float Dot(const vec3f &u, const vec3f &v)
{
	return u._x * v._x + u._y * v._y + u._z * v._z;
}

inline vec3f Normalize(const vec3f &vector)
{
	float inv_length = 1.0f / sqrtf(vector._x * vector._x + vector._y * vector._y + vector._z * vector._z);
	
	return vec3f(vector._x * inv_length, vector._y * inv_length, vector._z * inv_length);
}

inline vec3f Cross(const vec3f &u, const vec3f &v)
{
	float cx = u._y * v._z - v._y * u._z;
	float cy = u._z * v._x - v._z * u._x;
	float cz = u._x * v._y - v._x * u._y;

	return vec3f(cx, cy, cz);
}

#endif