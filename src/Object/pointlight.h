#ifndef _POINTLIGHT_H
#define _POINTLIGHT_H


#include "..\\Math\\vec3f.h"
#include "camera.h"

class PointLight
{
public:
	vec3f _p;
	vec3f _rgb;
	Camera _sight;

public:
	~PointLight(void);
	PointLight(void);
};


#endif