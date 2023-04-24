#include <chrono>
#include <DxLib.h>
#include "../Graphics/Image.h"
#include "../Graphics/PixelShader.h"
#include "../Graphics/ConstantBuffer.h"
#include "Application.h"

Application::~Application() = default;

bool Application::Run(void)
{
	if (!Initialize())
	{
		return false;
	}

	Update();

	DxLib_End();

	return true;
}

bool Application::Initialize(void)
{
	SetOutApplicationLogValidFlag(false);
	ChangeWindowMode(true);
	SetUseDirect3D11(true);

	return DxLib_Init() != -1;
}

void Application::Update(void)
{
	struct TestConstantBuffer
	{
		float time;
		float padding[3];
	};

	const Image image("Assets/Image/chimoshii.png");

	PixelShader pixelShader_("Assets/ShaderBinary/Pixel/TestOrigin.pso");

	auto constantBuffer = std::make_shared<ConstantBuffer<TestConstantBuffer>>();
	pixelShader_.SetConstantBuffer(constantBuffer, 0);

	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		SetDrawScreen(DX_SCREEN_BACK);
		ClsDrawScreen();

		auto time = static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - start).count()) / 1000000000;

		constantBuffer->GetValue() = { time };
		constantBuffer->Update();

		image.Draw(0.0f, 0.0f, pixelShader_);

		ScreenFlip();
	}
}
