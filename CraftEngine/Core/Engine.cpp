#include "Engine.h"
#include <Core/Win32Window.h>


Craft::Engine::Engine(uint32_t width, uint32_t height, const std::wstring title)
{
	// 창 객체 생성.
	window = std::make_unique<Win32Window>(width, height, this, title);
}

Craft::Engine::~Engine()
{
}

void Craft::Engine::Run()
{
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
	return;
}

void Craft::Engine::Quit()
{
}

LRESULT Craft::Engine::HandleMassege(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
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
	// ESC키 입력 처리.
	case WM_KEYDOWN:
	{
		if (wparam == VK_ESCAPE)
		{
			DestroyWindow(window);
		}
	}
	return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(window, &ps);

		// All painting occurs here, between BeginPaint and EndPaint.

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(window, &ps);
	}
	}

	return DefWindowProc(window, message, wparam, lparam);
}
