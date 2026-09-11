#include "LaunchApplication.h"


// 함수 선언.
LRESULT Win32MessageHandler(
	HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(window, message, wparam, lparam);
}

int LaunchApplication(HINSTANCE instance)
{
	// 창 만들기.
	// Register the window class.
	const wchar_t* className = L"Craft_Render_Engine_Class";

	// 창 만들 때 사용되는 정보 구조체.
	WNDCLASS wc = { };
	wc.lpfnWndProc = Win32MessageHandler;
	wc.hInstance = instance;
	wc.lpszClassName = className;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	// 클래스 등록.
	if (!RegisterClass(&wc))
	{
		return -1;
	}

	// Create the window.
	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		className,                     // Window class
		L"Learn to Program Windows",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,       // Parent window    
		NULL,       // Menu
		instance,  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, SW_SHOW);
	return 0;
}