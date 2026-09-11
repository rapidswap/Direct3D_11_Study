#include "LaunchApplication.h"


// 함수 선언.
LRESULT Win32MessageHandler(
	HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
	// 메시지 처리.
	switch (message)
	{
		// 창 닫기 메시지
	case WM_CLOSE:
	{
		// 창 객체 삭제.
		DestroyWindow(window);
	}
	return 0;

	// 창 삭제 이벤트 처리.
	case WM_DESTROY:
	{
		// 프로그램 종료 요청(종료 메시지 발행).
		PostQuitMessage(0);
	}
	return 0;
	}

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
	HWND hwnd = CreateWindow(
		className,                     // Window class
		L"Learn to Program Windows",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		nullptr,       // Parent window    
		nullptr,       // Menu
		instance,  // Instance handle
		nullptr        // Additional application data
	);

	if (hwnd == nullptr)
	{
		return 0;
	}

	// 창 보이기 모드 설정.
	ShowWindow(hwnd, SW_SHOW);

	// 이벤트(메세지) 처리 루프.
	MSG message = {};
	while (message.message != WM_QUIT)
	{
		// 창에 메시지가 발생한 경우의 처리
		if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		// 엔지 루프 처리 등...
		else
		{
			
		}
	}
	return 0;
}