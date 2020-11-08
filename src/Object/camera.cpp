#include "camera.h"


Camera::~Camera(void)
{
}

Camera::Camera(void)
{
}

float *Camera::View(void)
{
	return _view._m;
}

float *Camera::Perspective(void)
{
	return _perspective._m;
}

void Camera::SetMatrix(const vec3f position, const vec3f look_at, const vec3f up, const int window_width, const int window_height, const float fov)
{
	vec3f w(Normalize(position - look_at));
	vec3f u(Normalize(Cross(up, w)));
	vec3f v(Normalize(Cross(w, u)));

	float u_dot_position = Dot(u, position);
	float v_dot_position = Dot(v, position);
	float w_dot_position = Dot(w, position);

	_view._m[0] = u._x;   _view._m[1] = u._y;   _view._m[2] = u._z;   _view._m[3] = -u_dot_position;
	_view._m[4] = v._x;   _view._m[5] = v._y;   _view._m[6] = v._z;   _view._m[7] = -v_dot_position;
	_view._m[8] = w._x;   _view._m[9] = w._y;   _view._m[10] = w._z;  _view._m[11] = -w_dot_position;
	_view._m[12] = 0.0f;  _view._m[13] = 0.0f;  _view._m[14] = 0.0f;  _view._m[15] = 1.0f;

	float aspect = (float)window_width / (float)window_height;
	float near = (int)(Length(position - look_at) - 10.0f);
	float far = (int)(Length(position - look_at) + 10.0f);
	float top = tan(fov / 2) * near;
	float bottom = -top;
	float left = bottom * aspect;
	float right = top * aspect;

	_perspective._m[0] = near / right;   _perspective._m[1] = 0.0f;           _perspective._m[2] = (right + left) / (right - left);   _perspective._m[3] = 0.0f;
	_perspective._m[4] = 0.0f;           _perspective._m[5] = (near / top);   _perspective._m[6] = (top + bottom) / (top - bottom);   _perspective._m[7] = 0.0f;
	_perspective._m[8] = 0.0f;           _perspective._m[9] = 0.0f;           _perspective._m[10] = -(far + near) / (far - near);     _perspective._m[11] = -((2 * far * near) / (far - near));
	_perspective._m[12] = 0.0f;          _perspective._m[13] = 0.0f;          _perspective._m[14] = -1.0f;                            _perspective._m[15] = 0.0f;

	return;
}