#include <chrono>
#include <DxLib.h>
#include "Application.h"
#include "../Graphics/Image.h"
#include "../Graphics/PixelShader.h"
#include "../Graphics/ConstantBuffer.h"
#include "../Common/StopWatch.h"

bool Application::Run(void)
{
	//初期化
	if (!Initialize())
	{
		return false;
	}

	Update();		//更新

	DxLib_End();	//DXライブラリ終了処理

	return true;
}

bool Application::Initialize(void)
{
	SetOutApplicationLogValidFlag(false);		//ログファイルの出力無効化
	ChangeWindowMode(true);					//ウィンドウモードに変更
	SetUseDirect3D11(true);					//DirectX11を使用

	return DxLib_Init() != -1;					//DXライブラリ初期化処理
}

void Application::Update(void)
{
	//定数バッファとして転送するための構造体(DirectX11は16byteアライメントのためpaddingで調整)
	struct TestConstantBuffer
	{
		float time;				//経過時間
		float padding[3];		//パディング
	};
	const Image image("Assets/Image/chimoshii.png");							//画像オブジェクト生成

	PixelShader pixelShader_("Assets/ShaderBinary/Pixel/TestOrigin.pso");		//ピクセルシェーダーオブジェクト生成

	auto constantBuffer = std::make_shared<ConstantBuffer<TestConstantBuffer>>();		//定数バッファオブジェクト生成
	pixelShader_.SetConstantBuffer(constantBuffer, 0);							//ピクセルシェーダーの0番スロットに定数バッファをセット

	StopWatch stopWatch;		//時間計測用オブジェクト生成
	stopWatch.Start();			//計測開始

	//DXライブラリ側で異常を検知した場合かエスケープキーを押下した際にゲームループを出る
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		SetDrawScreen(DX_SCREEN_BACK);		//バックスクリーンにスクリーンをセット
		ClsDrawScreen();					//スクリーンを初期化

		constantBuffer->GetValue().time = stopWatch.GetNowCount();		//CPU側に確保されたバッファに経過時間を書き込み
		constantBuffer->Update();										//CPU→GPUにバッファを転送

		image.Draw(0.0f, 0.0f, pixelShader_);						//ピクセルシェーダーを使用して(0,0)の位置に画像を描画

		ScreenFlip();													//実際の画面に反映
	}
}
