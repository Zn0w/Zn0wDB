#include <windows.h>

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous_instance, LPSTR cmd, int cmd_show)
{
	MessageBox(NULL, "Hello World", "This is a test!", MB_OK);
	
	return 0;
}