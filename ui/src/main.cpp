#include <windows.h>
#include <stdio.h>

#include "window.h"

bool running;


LRESULT CALLBACK WindowProc(
	HWND   handle_window,
	UINT   message,
	WPARAM wParam,
	LPARAM lParam
)
{	
	switch (message)
	{
		case WM_DESTROY :
		{
			running = false;
			OutputDebugString("WM_DESTROY\n");
			PostQuitMessage(0);
		}break;

		case WM_CLOSE :
		{
			running = false;
			OutputDebugString("WM_CLOSE\n");
		}break;

		case WM_ACTIVATEAPP :
		{
			OutputDebugString("WM_ACTIVATEAPP\n");
		}break;

		default:
		{
			return DefWindowProcA(handle_window, message, wParam, lParam);
		}break;
	}
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous_instance, LPSTR cmd, int cmd_show)
{
	Window window_data;
	window_data.x = 250;
	window_data.y = 250;
	window_data.width = 250;
	window_data.height = 250;
	window_data.title = "Test Window Title";

	// 'A' in the end of WNDCLASS means to handle strings in window as ansi code
	WNDCLASSA window_class = {};	// initializes every element of windows class  to 0

	window_class.hbrBackground = (HBRUSH) COLOR_WINDOW;		// Set a default window color
	window_class.hCursor = LoadCursor(NULL, IDC_ARROW);	// Enable a cursor in window
	window_class.lpfnWndProc = WindowProc;
	window_class.hInstance = instance;
	window_class.lpszClassName = "Zn0wDBWindowClass";

	if (RegisterClassA(&window_class))
	{
		HWND window_handle = CreateWindowA(
			"Zn0wDBWindowClass",
			window_data.title,
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			window_data.x,
			window_data.y,
			window_data.width,
			window_data.height,
			NULL,
			NULL,
			instance,
			NULL
			);

		if (window_handle)
		{
			running = true;

			while (running)
			{
				MSG message;
				if (GetMessageA(&message, NULL, NULL, NULL))
				{
					TranslateMessage(&message);
					DispatchMessageA(&message);		// Send message to the WindowProc
				}
				else
				{
					break;
				}
			}
		}
	}

	
	return 0;
}