#ifndef _CAMERA_H
#define _CAMERA_H


#include "..\\Math\\vec3f.h"
#include "..\\Math\\\matrix.h"

class Camera
{
private:
	Mat4x4 _view;
	Mat4x4 _perspective;

public:
	~Camera(void);
	Camera(void);

	float *View(void);
	float *Perspective(void);
	void SetMatrix(const vec3f position, const vec3f look_at, const vec3f up, const int window_width, const int window_height, const float fov);
};


#endif