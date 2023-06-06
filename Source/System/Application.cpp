#include <DxLib.h>
#include "Application.h"
#include "Graphics/Drawable/Image.h"
#include "Graphics/Drawable/Screen.h"
#include "Graphics/Drawable/Model.h"
#include "Graphics/Camera/PerspectiveCamera.h"
#include "Graphics/Shader/VertexShader.h"
#include "Graphics/Shader/PixelShader.h"
#include "Graphics/Shader/ConstantBuffer.h"
#include "Common/StopWatch.h"

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
	ChangeWindowMode(true);						//ウィンドウモードに変更
	SetUseDirect3D11(true);						//DirectX11を使用

	if(DxLib_Init() == -1)
	{
		return false;
	}

	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);

	return true;					//DXライブラリ初期化処理
}

void Application::Update(void)
{
	//定数バッファとして転送するための構造体(DirectX11は16byteアライメントのためpaddingで調整)
	struct TestConstantBuffer
	{
		float time;				//経過時間
		float padding[3];		//パディング
	};
	

	const Image image("Assets/Image/food_udon_goboten.png");	//画像オブジェクト生成

	Model model("Assets/Model/cube.mv1");						//モデルオブジェクト生成
	model.SetPosition({ 0.f, 0.f, 0.f });						//位置を(0,0,0)に設定

	PerspectiveCamera camera;									//カメラオブジェクト生成
	camera.SetPosition({ -300.f, 300.f, -300.f});				//位置を(-300, 300, -300)に設定

	PixelShader imagePixelShader("Assets/ShaderBinary/Pixel/ImagePixelShader.pso");					//画像用のピクセルシェーダーオブジェクト生成

	VertexShader modelVertexShader("Assets/ShaderBinary/Vertex/ModelVertexShader.vso");				//モデル用の頂点シェーダーオブジェクト生成
	PixelShader modelPixelShader("Assets/ShaderBinary/Pixel/ModelPixelShader.pso");					//モデル用のピクセルシェーダーオブジェクト生成

	auto constantBuffer = std::make_shared<ConstantBuffer<TestConstantBuffer>>();		//定数バッファオブジェクト生成
	imagePixelShader.SetConstantBuffer(constantBuffer, 3);								//ピクセルシェーダーの3番スロットに定数バッファをセット

	auto screen = Screen(640, 480, true);												//スクリーンを作成
	auto& backScreen = Screen::GetBackScreen();											//バックスクリーンを取得

	StopWatch stopWatch;		//時間計測用オブジェクト生成
	stopWatch.Start();			//計測開始

	//DXライブラリ側で異常を検知した場合かエスケープキーを押下した際にゲームループを出る
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		constantBuffer->GetValue().time = stopWatch.GetNowCount();		//CPU側に確保されたバッファに経過時間を書き込み
		constantBuffer->Update();										//CPU→GPUにバッファを転送

		//ここから描画処理

		screen.Setup();				//スクリーンをセット
		camera.Setup();				//カメラのセット
		screen.Clear();				//スクリーンを初期化

		image.Draw(0.0f, 0.0f, imagePixelShader);						//ピクセルシェーダーを使用して(0,0)の位置に画像を描画
		//model.Draw(modelVertexShader, modelPixelShader);				//シェーダーを利用したモデルの描画


		backScreen.Setup();
		backScreen.Clear();

		screen.Draw(0.0f, 0.0f, true);

		Screen::Flip();			//実際の画面に反映
	}
}
