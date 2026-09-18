#include "Engine.h"
#include <Core/Win32Window.h>
#include <Graphics/Renderer.h>


#if _DEBUG
#include <iostream>
#endif

Craft::Engine::Engine(uint32_t width, uint32_t height, const std::wstring title)
{
	// 창 객체 생성.
	window = std::make_unique<Win32Window>(width, height, this, title);

	// 렌더러 객체 생성.
	renderer = std::make_unique<Renderer>(*window);
}

Craft::Engine::~Engine()
{
}

void Craft::Engine::Run()
{
	// 고해상도 타이머 주파수 가져오기.
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	// 델타 타임 구하는 람다 함수.
	auto GetDeltaTime = [&frequency](int64_t& current, int64_t& previous) -> float
		{
			// 현재 시간 가져오기.
			LARGE_INTEGER counter;
			QueryPerformanceCounter(&counter);

			current = counter.QuadPart;

			return static_cast<float>(current - previous) / static_cast<float>(frequency.QuadPart);
		};

	// 프레임 계산을 위한 변수.
	LARGE_INTEGER initialCounter;
	QueryPerformanceCounter(&initialCounter);

	int64_t current = initialCounter.QuadPart;
	int64_t previous = current;

	// 고정 프레임 처리를 위한 값.
	const float framerate = 120.0f;
	const float oneFrameTime = 1.0f / framerate;

	// 스레드 재우는 간격 설정.
	timeBeginPeriod(1);

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
			Draw();
			
			// 프레임 시간 구하기.
			float deltaTime = GetDeltaTime(current, previous);

			// 대기 시간 계산.
			float remainingTime = oneFrameTime - deltaTime;

			// 스레드 재우기.
			while (remainingTime >= 0.002f)
			{
				// Sleep에서 0넣을때와 1넣을때 차이.
				Sleep(1);

				// 프레임 시간 구하기.
				deltaTime = GetDeltaTime(current, previous);

				// 남은 시간 계산.
				remainingTime = oneFrameTime - deltaTime;
			}

			while (remainingTime > 0.0f)
			{

				// 프레임 시간 구하기.
				deltaTime = GetDeltaTime(current, previous);

				// 남은 시간 계산.
				remainingTime = oneFrameTime - deltaTime;
			}

			// 이전 시간 기록.
			previous = current;

#if _DEBUG
			std::cout << "DeltaTime: " << deltaTime << " | FPS:" << (1.0f / deltaTime) << "\n";
#endif
		}
	}
	// 스레드 간격 원상 복구.
	timeEndPeriod(1);
}

void Craft::Engine::Quit()
{
}

void Craft::Engine::Draw()
{
	// 이벤트 전달.
	if (renderer)
	{
		renderer->Draw(0.6f, 0.7f, 0.8f, 0);
	}
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
