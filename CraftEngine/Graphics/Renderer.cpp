#include "Renderer.h"
#include <cstdint>

namespace Craft
{
	Renderer::Renderer()
	{
		CreateDevices();
	}
	Renderer::~Renderer()
	{
	}
	void Renderer::CreateDevices()
	{
		uint32_t flag = 0;

#if _DEBUG
		flag = D3D11_CREATE_DEVICE_DEBUG;
#endif

		// 그래픽스 api 버전.
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0
		};

		D3D_FEATURE_LEVEL selectedFeatureLevel = {};

		// 장치 생성 함수 호출.
		auto result = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			flag,
			featureLevels,
			_countof(featureLevels),
			D3D11_SDK_VERSION,
			&device,
			nullptr, //&selectedFeatureLevel,
			&context
		);
	}
}