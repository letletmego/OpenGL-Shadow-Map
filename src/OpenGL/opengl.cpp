#include "opengl.h"
#include <gl\\glew.h>


OpenGL::~OpenGL(void)
{
}

OpenGL::OpenGL()
	: _window_width(0)
	, _window_height(0)
	, _show_depth(false)
	, _canvas_shader()
	, _depth_shader()
	, _render_shader()
	, _sight()
	, _theta(0.0f)
	, _model_transform()
	, _light_transform()
	, _light()
	, _plane()
	, _cube1()
	, _cube2()
	, _canvas()
	, _depth_map()
{
}

void OpenGL::OpenGLInitialize(const int width, const int height)
{
	// Set the initial viewport of window
	SetOpenGLViewPort(width, height);
	// Sets the current clear color for use in clearing color buffers(GL_COLOR_BUFFER_BIT)
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// Sets the current depth value for use in clearing depth buffers(GL_DEPTH_BUFFER_BIT)
	glClearDepth(1.0f);
	// Turn on the depth test
	glEnable(GL_DEPTH_TEST);

	ObjectInitialize();
	
	DepthShaderInitialize();
	
	RenderShaderInitialize();
	
	CanvasShaderInitialize();

	return;
}

void OpenGL::SetOpenGLViewPort(const int width, const int height)
{
	_window_width = width;
	_window_height = height;
	glViewport(0, 0, _window_width, _window_height);

	return;
}

void OpenGL::ShowDepthMap(void)
{
	if (_show_depth == false)
		_show_depth = true;
	else
		_show_depth = false;

	return;
}

void OpenGL::Rotation(void)
{ 
	if (_theta > 2.0f * PI)
		_theta = 0.0f;
	else
		_theta += PI / 180.0f;

	_model_transform._m[0] = cos(_theta);
	_model_transform._m[2] = sin(_theta);
	_model_transform._m[8] = -sin(_theta);
	_model_transform._m[10] = cos(_theta);

	_light_transform._m[0] = cos(-_theta);
	_light_transform._m[2] = sin(-_theta);
	_light_transform._m[8] = -sin(-_theta);
	_light_transform._m[10] = cos(-_theta);

	glUseProgram(_depth_shader._program);
	UniformMat4x4(&_depth_shader._program, _depth_shader.GetVariable(0), _model_transform._m, GL_TRUE);
	glUseProgram(0);

	glUseProgram(_render_shader._program);
	UniformMat4x4(&_render_shader._program, _render_shader.GetVariable(0), _model_transform._m, GL_TRUE);
	UniformMat4x4(&_render_shader._program, _render_shader.GetVariable(1), _light_transform._m, GL_TRUE);
	glUseProgram(0);

	return;
}

void OpenGL::ObjectInitialize(void)
{
	_sight.SetMatrix(vec3f(9.8f, 10.0f, 15.0f), vec3f(0.0f), vec3f(0.0f, 1.0f, 0.0f), _window_width, _window_height, PI / 6.0f);
	//_sight.SetMatrix(vec3f(-10.0f, 9.0f, 10.0f), vec3f(0.0f), vec3f(0.0f, 1.0f, 0.0f), _window_width, _window_height, PI / 6.0f);

	_light._p = vec3f(-10.0f, 9.0f, 10.0f);
	_light._rgb = vec3f(1.0f * 10.0f);
	_light._sight.SetMatrix(_light._p, vec3f(0.0f), vec3f(0.0f, 1.0f, 0.0f), _window_width, _window_height, PI / 6.0f);

	_plane.BufferDataInitialize();
	_cube1.BufferDataInitialize();
	_cube2.BufferDataInitialize();
	_canvas.BufferDataInitialize();
	_depth_map.Initialize(_window_width, _window_height);

	return;
}

void OpenGL::DepthShaderInitialize(void)
{
	_depth_shader.Initialize(2);
	_depth_shader.AddVariable("model_transform");
	_depth_shader.AddVariable("light_view");
	_depth_shader.AddVariable("light_perspective");
	_depth_shader.AddVariable("vs_object_vertex");
	_depth_shader.CompileVertexShader("OpenGL\\Shader\\depth.vs", "OpenGL\\Shader\\depth_debug.txt");
	_depth_shader.CompileFragmentShader("OpenGL\\Shader\\depth.fs", "OpenGL\\Shader\\depth_debug.txt");
	_depth_shader.LinkShader("OpenGL\\Shader\\depth_debug.txt");

	glUseProgram(_depth_shader._program);
	UniformMat4x4(&_depth_shader._program, _depth_shader.GetVariable(0), _model_transform._m, GL_TRUE);
	UniformMat4x4(&_depth_shader._program, _depth_shader.GetVariable(1), _light._sight.View(), GL_TRUE);
	UniformMat4x4(&_depth_shader._program, _depth_shader.GetVariable(2), _light._sight.Perspective(), GL_TRUE);
	glUseProgram(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return;
}

void OpenGL::RenderShaderInitialize(void)
{
	_render_shader.Initialize(2);
	_render_shader.AddVariable("model_transform");
	_render_shader.AddVariable("light_transform");
	_render_shader.AddVariable("view");
	_render_shader.AddVariable("perspective");
	_render_shader.AddVariable("light_view");
	_render_shader.AddVariable("light_perspective");
	_render_shader.AddVariable("light_position");
	_render_shader.AddVariable("light_rgb");
	_render_shader.AddVariable("vs_object_vertex");
	_render_shader.AddVariable("vs_object_normal");
	_render_shader.AddVariable("vs_object_color");
	_render_shader.AddVariable("depth_map");
	_render_shader.CompileVertexShader("OpenGL\\Shader\\render.vs", "OpenGL\\Shader\\render_debug.txt");
	_render_shader.CompileFragmentShader("OpenGL\\Shader\\render.fs", "OpenGL\\Shader\\render_debug.txt");
	_render_shader.LinkShader("OpenGL\\Shader\\render_debug.txt");

	glUseProgram(_render_shader._program);
	UniformMat4x4(&_render_shader._program, _render_shader.GetVariable(0), _model_transform._m, GL_TRUE);
	UniformMat4x4(&_render_shader._program, _render_shader.GetVariable(1), _light_transform._m, GL_TRUE);
	UniformMat4x4(&_render_shader._program, _render_shader.GetVariable(2), _sight.View(), GL_TRUE);
	UniformMat4x4(&_render_shader._program, _render_shader.GetVariable(3), _sight.Perspective(), GL_TRUE);
	UniformMat4x4(&_render_shader._program, _render_shader.GetVariable(4), _light._sight.View(), GL_TRUE);
	UniformMat4x4(&_render_shader._program, _render_shader.GetVariable(5), _light._sight.Perspective(), GL_TRUE);
	Uniform3fv(&_render_shader._program, _render_shader.GetVariable(6), (float *)&_light._p, GL_TRUE);
	Uniform3fv(&_render_shader._program, _render_shader.GetVariable(7), (float *)&_light._rgb, GL_TRUE);
	//GLSLSampler(&_render_shader._program, _render_shader.GetVariable(9), 0);
	glUseProgram(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return;
}

void OpenGL::CanvasShaderInitialize(void)
{
	_canvas_shader.Initialize(2);
	_canvas_shader.AddVariable("depth_map");
	_canvas_shader.AddVariable("vs_canvas_vertex");
	_canvas_shader.AddVariable("vs_canvas_st");
	_canvas_shader.CompileVertexShader("OpenGL\\Shader\\canvas.vs", "OpenGL\\Shader\\canvas_debug.txt");
	_canvas_shader.CompileFragmentShader("OpenGL\\Shader\\canvas.fs", "OpenGL\\Shader\\canvas_debug.txt");
	_canvas_shader.LinkShader("OpenGL\\Shader\\canvas_debug.txt");

	//glUseProgram(_canvas_shader._program);
	//GLSLSampler(&_canvas_shader._program, _canvas_shader.GetVariable(0), 0);
	//glUseProgram(0);

	unsigned int var_location = 0;

	glBindVertexArray(_canvas._vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, _canvas._vbo[0]);
	var_location = glGetAttribLocation(_canvas_shader._program, _canvas_shader.GetVariable(1));
	glVertexAttribPointer(var_location, CANVAS_DATA_COL, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(var_location);

	glBindBuffer(GL_ARRAY_BUFFER, _canvas._vbo[1]);
	var_location = glGetAttribLocation(_canvas_shader._program, _canvas_shader.GetVariable(2));
	glVertexAttribPointer(var_location, CANVAS_DATA_COL - 1, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(var_location);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return;
}

void OpenGL::Render(void)
{
	DepthRendering();

	SceneRendering();

	CanvasRendering();

	glUseProgram(0);

	glFlush();

	return;
}

void OpenGL::DepthRendering(void)
{
	// Draw into the frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, _depth_map._fbo);
	// Set up the viewport of frame buffer which we create
	glViewport(0, 0, _depth_map._width, _depth_map._height);
	// Use 1.0f to clean the depth of frame buffer
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); 
	glCullFace(GL_BACK);

	glUseProgram(_depth_shader._program);

	unsigned int var_location;
	var_location = glGetAttribLocation(_depth_shader._program, _depth_shader.GetVariable(3));

	glBindVertexArray(_plane._vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, _plane._vbo[0]);
	glVertexAttribPointer(var_location, PLANE_DATA_COL, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(var_location);
	glDrawArrays(GL_TRIANGLES, 0, PLANE_DATA_ROW);

	glBindVertexArray(_cube1._vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, _cube1._vbo[0]);
	glVertexAttribPointer(var_location, CUBE_DATA_COL, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(var_location);
	glDrawArrays(GL_TRIANGLES, 0, CUBE_DATA_ROW);

	glBindVertexArray(_cube2._vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, _cube2._vbo[0]);
	glVertexAttribPointer(var_location, CUBE_DATA_COL, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(var_location);
	glDrawArrays(GL_TRIANGLES, 0, CUBE_DATA_ROW);

	glDisableVertexAttribArray(var_location);

	glDisable(GL_CULL_FACE);
	// Back to default frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return;
}

void OpenGL::SceneRendering(void)
{
	if (_show_depth == true)
		return;

	glViewport(0, 0, _window_width, _window_height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(_render_shader._program);
	unsigned int var_vertex_location = glGetAttribLocation(_render_shader._program, _render_shader.GetVariable(8));
	unsigned int var_normal_location = glGetAttribLocation(_render_shader._program, _render_shader.GetVariable(9));
	unsigned int var_color_location = glGetAttribLocation(_render_shader._program, _render_shader.GetVariable(10));

	glBindTexture(GL_TEXTURE_2D, _depth_map._texture_object);

	// Plane property
	glBindVertexArray(_plane._vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, _plane._vbo[0]);
	glVertexAttribPointer(var_vertex_location, PLANE_DATA_COL, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(var_vertex_location);

	glBindBuffer(GL_ARRAY_BUFFER, _plane._vbo[1]);
	glVertexAttribPointer(var_normal_location, PLANE_DATA_COL, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(var_normal_location);

	glBindBuffer(GL_ARRAY_BUFFER, _plane._vbo[2]);
	glVertexAttribPointer(var_color_location, PLANE_DATA_COL, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(var_color_location);

	glDrawArrays(GL_TRIANGLES, 0, PLANE_DATA_ROW);

	// Right cube property
	glBindVertexArray(_cube1._vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, _cube1._vbo[0]);
	glVertexAttribPointer(var_vertex_location, CUBE_DATA_COL, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(var_vertex_location);

	glBindBuffer(GL_ARRAY_BUFFER, _cube1._vbo[1]);
	glVertexAttribPointer(var_normal_location, CUBE_DATA_COL, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(var_normal_location);

	glBindBuffer(GL_ARRAY_BUFFER, _cube1._vbo[2]);
	glVertexAttribPointer(var_color_location, CUBE_DATA_COL, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(var_color_location);

	glDrawArrays(GL_TRIANGLES, 0, CUBE_DATA_ROW);

	// Left cube property
	glBindVertexArray(_cube2._vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, _cube2._vbo[0]);
	glVertexAttribPointer(var_vertex_location, CUBE_DATA_COL, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(var_vertex_location);

	glBindBuffer(GL_ARRAY_BUFFER, _cube2._vbo[1]);
	glVertexAttribPointer(var_normal_location, CUBE_DATA_COL, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(var_normal_location);

	glBindBuffer(GL_ARRAY_BUFFER, _cube2._vbo[2]);
	glVertexAttribPointer(var_color_location, CUBE_DATA_COL, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(var_color_location);

    glDrawArrays(GL_TRIANGLES, 0, CUBE_DATA_ROW);

	return;
}

void OpenGL::CanvasRendering(void)
{
	glClear(GL_DEPTH_BUFFER_BIT);

	if (_show_depth == false)
		glViewport(_window_width * 0.75, _window_height * 0.75, _window_width * 0.25, _window_height * 0.25);
	else
		glViewport(0.0f, 0.0f, _window_width, _window_height);

	glUseProgram(_canvas_shader._program);

	glBindTexture(GL_TEXTURE_2D, _depth_map._texture_object);

	glBindVertexArray(_canvas._vao[0]);
	glDrawArrays(GL_TRIANGLES, 0, CANVAS_DATA_ROW);

	return;
}