#ifndef _WINDOW_H
#define _WINDOW_H

#include <Windows.h>

class OpenGL;

class Window
{
private:
	HWND _hWnd;
	int _width;
	int _height;
	OpenGL *_gl;

public:
	~Window(void);
	Window(void);

	int Width(void);
	int Height(void);
	OpenGL *OpenGLPtr(void) const;
	bool Initialize(HINSTANCE &hInstance, const int width, const int height);
	bool CreateOpenGLContext(void);
	void Show(void);
	void MassageLoop(void);
	void Paint(HWND hWnd);
	void ReSize(const int width, const int height);
	void OnKeyDown(UINT key);
};

extern Window my_window;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);

#endif