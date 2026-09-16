#include "Renderer.h"
#include <Core/Win32Window.h>
#include <cstdint>

namespace Craft
{
	Renderer::Renderer(const Win32Window& window)
	{
		// Device/Context 생성.
		CreateDevices();

		// 스왑체인 생성.
		CreateSwapChain(window);
	}
	Renderer::~Renderer()
	{
		if (device)
		{
			device->Release();
			device = nullptr;
		}
		if (context)
		{
			context->Release();
			context = nullptr;
		}
		if (swapChain)
		{
			swapChain->Release();
			swapChain = nullptr;
		}
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

		// 실패 확인.
		//if(SUCCEEDED(result))
		if (FAILED(result))
		{
			__debugbreak();
			MessageBoxA(nullptr, "Failed to create device", "D3D Error", MB_OK);
		}
	}
	void Renderer::CreateSwapChain(const Win32Window& window)
	{
		// 스왑체인 생성을 위한 객체 생성.
		IDXGIFactory* factory = nullptr;
		
		// auto result = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&factory));
		auto result = CreateDXGIFactory(IID_PPV_ARGS(&factory));


		if (FAILED(result))
		{
			__debugbreak();
			// ...
			return;
		}


		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferDesc.Width = window.GetWidth();
		swapChainDesc.BufferDesc.Height = window.GetHeight();
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2;
		swapChainDesc.OutputWindow = window.GetHandle();
		swapChainDesc.Windowed = true;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

		// 스왑체인 생성.
		result = factory->CreateSwapChain(device, &swapChainDesc, &swapChain);

		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		// 해제.
		if (factory)
		{
			factory->Release();
			factory = nullptr;
		}
	}
}