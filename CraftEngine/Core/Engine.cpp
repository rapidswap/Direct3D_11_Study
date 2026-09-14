#include "Engine.h"
#include <Core/Win32Window.h>


Craft::Engine::Engine(uint32_t width, uint32_t height, const std::wstring title)
{
	// 창 객체 생성.
	window = std::make_unique<Win32Window>(width, height, title);
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
