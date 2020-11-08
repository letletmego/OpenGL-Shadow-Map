#include "window.h"
#include "..\OpenGL\opengl.h"


Window::~Window(void)
{
	delete _gl;
	_gl = 0x00;
}

Window::Window(void)
	: _hWnd(0x00)
	, _width(0)
	, _height(0)
	, _gl(0x00)
{
}

int Window::Width(void)
{
	return _width;
}

int Window::Height(void)
{
	return _height;
}

OpenGL *Window::OpenGLPtr(void) const
{
	return _gl;
}

bool Window::Initialize(HINSTANCE &hInstance, const int width, const int height)
{
	// HINSTANCE -> handle of program
	// Class for creating the main window
	WNDCLASSEX wcex;
	memset(&wcex, 0, sizeof(WNDCLASSEX));

	const char *szWindowClass = "win32Class";

	// Register the window class
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	//wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYICON));
	wcex.hIcon = LoadIcon(hInstance, 0);
	wcex.hCursor = LoadCursor(hInstance, IDC_ARROW);
	//wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	//wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYICON));
	wcex.hIconSm = LoadIcon(hInstance, 0);

	if(RegisterClassEx(&wcex) == NULL)
	{
		   ::MessageBox(NULL,  "RegisterClassEx failed!", "ERROR", MB_ICONEXCLAMATION | MB_OK);
		   return false;
	}

	// Create window
	_width  = width;
	_height = height;

	_hWnd = CreateWindowEx(WS_EX_CLIENTEDGE,
		szWindowClass,
		"OpenGL Shadow Map",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,
		NULL, NULL, hInstance, NULL);

	if(_hWnd == NULL)
	{
		::MessageBox(NULL, "CreateWindow failed!", "ERROR", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	// Matching a device context to a pixel format.
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR), // Size of the pfd
		1,                             // Version number
		PFD_DRAW_TO_WINDOW |           // Supprot window
		PFD_SUPPORT_OPENGL |           // Support OpenGL
		PFD_DOUBLEBUFFER,              // Support double buffer
		PFD_TYPE_RGBA,                 // RGBA type
		24,                            // 24 bits color depth
		0, 0, 0, 0, 0, 0,              // Color bits ignore
		0,                             // No alpha buffer
		0,                             // Shift bits ignore
		0,                             // No accumulation buffer
		0,                             // Accum bits ignore
		32,                            // 32 bits z-buffer
		0,                             // No stencil buffer
		0,                             // No auxiliary buffer
		PFD_MAIN_PLANE,                // Main layer
		0,                             // Reserved
		0, 0, 0                        // layer masks ignored
	};

	// Obtain a device context for the window
	// A device context is a structure that defines a set of graphic objects 
	// and their associated attributes
	// ,as well as the graphic modes that affect output
	HDC hDC = GetDC(_hWnd);
	// Get the device context's best, available pixel format match
	int PixelFormat = ChoosePixelFormat(hDC, &pfd);
	// Examining a device context's current pixel format 
	if(PixelFormat == 0)
	{
		::MessageBox(NULL, "ChoosePixelFormat failed!", "ERROR", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	// Make that match the device context's current pixel format 
	bool setPF = SetPixelFormat(hDC, PixelFormat, &pfd);
	if(setPF == false)
	{
		::MessageBox(NULL, "SetPixelFormat failed!", "ERROR", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	return true;
}

bool Window::CreateOpenGLContext(void)
{
	if (_gl != 0x00)
		return false;

	HDC hDC = GetDC(_hWnd);
	// All calls pass through a rendering context
	// Create an OpenGL rendering context
	HGLRC hGLRC = wglCreateContext(hDC);
	if(hGLRC == NULL)
	{
		MessageBox(NULL, "wglCreateContext failed!", "ERROR", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}
	// The current rendering context uses the hdc device context until the rendering context is no longer current
	if(wglMakeCurrent(hDC, hGLRC) == false)
	{
		MessageBox(NULL, "wglMakeCurrent failed!", "ERROR", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	if(glewInit() != GLEW_OK)
    {
        MessageBox(NULL, "glew failed to init!", "ERROR", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

	_gl = new OpenGL();
	_gl->OpenGLInitialize(_width, _height);

	return false;
}

void Window::Show(void)
{
	ShowWindow(_hWnd, SW_SHOWNORMAL);

	return;
}

void Window::MassageLoop()
{
	MSG Msg;

	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return;
}

void Window::Paint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);

	_gl->Render();

	SwapBuffers(hDC);
	EndPaint(hWnd, &ps);

	return;
}

void Window::ReSize(const int width, const int height)
{
	_width = width;
	_height = height;

	_gl->SetOpenGLViewPort(width, height);

	return;
}

void Window::OnKeyDown(UINT key)
{
	if (_gl == 0x00)
		return;

	switch(key)
	{
		case '1':
			_gl->Rotation();
			break;

		case '2':
			_gl->ShowDepthMap();
			break;
	}

	::SendMessage(_hWnd, WM_PAINT, 0, 0);

	return;
}

// -------------------------------------------------------------------------------------------------------------
Window my_window;
// wParam and lParam are 32 bits in win32
// lParam is HWND(window handle) to control which send the message or NULL if the message isn't from the control
// wParam contains two values -> HIWORD(wParam) and LOWORD(wParam)
// HIWORD(wParam) is notification message
// LOWORD(wParam) is the control or menu ID
// HIWORD -> (0xFFFF0000)
// LOWORD -> (0x0000FFFF)
// DWORD -> double word 32 bits
LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uiMsg)
	{
		// When the window is closed
		case WM_DESTROY:
			// Post WM_QUIT message to the message loop
			PostQuitMessage(0);
			break;

		case WM_PAINT:
			my_window.Paint(hWnd);
			break;

		case WM_SIZE:
			my_window.ReSize(LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_KEYDOWN:
			my_window.OnKeyDown((UINT)wParam);
			break;

		default:
			return DefWindowProc(hWnd, uiMsg, wParam, lParam);
	}

	return 0;
}