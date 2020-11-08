#include "Win32\\window.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	my_window.Initialize(hInstance, 800, 600);
	my_window.CreateOpenGLContext();
	my_window.Show();
	my_window.MassageLoop();

	return 0;
}