#pragma once

#include <Windows.h>

namespace Craft
{
	// Window에서 Engine으로 메시지 처리를 전달할 때 사용할 인터페이스.
	class IMessageHandler
	{
	public:
		virtual LRESULT HandleMassege(HWND window, UINT message, WPARAM wparam, LPARAM lparam) = 0;

	};
}