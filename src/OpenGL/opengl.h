#ifndef _OPEN_GL
#define _OPEN_GL


#include "glshader.h"
#include "..\\Object\\camera.h"
#include "..\\Object\\pointlight.h"
#include "..\\Object\\plane.h"
#include "..\\Object\\cube.h"
#include "..\\Object\\depthmap.h"

class OpenGL
{
private:
	float _window_width;
	float _window_height;
	bool _show_depth;
	GLShader _canvas_shader;
	GLShader _depth_shader;
	GLShader _render_shader;
	Camera _sight;
	float _theta;
	Mat4x4 _model_transform;
	Mat4x4 _light_transform;
	PointLight _light;
	Plane _plane;
	Cube1 _cube1;
	Cube2 _cube2;
	Canvas _canvas;
	DepthMap _depth_map;

public:
	~OpenGL(void);
	OpenGL(void);

public:
	void OpenGLInitialize(const int width, const int height);
	void SetOpenGLViewPort(const int width, const int height);
	void ShowDepthMap(void);
	void Rotation(void);
	void ObjectInitialize(void);
	void RenderShaderInitialize(void);
	void DepthShaderInitialize(void);
	void CanvasShaderInitialize(void);
	void Render(void);
	void DepthRendering(void);
	void SceneRendering(void);
	void CanvasRendering(void);
};

#endif