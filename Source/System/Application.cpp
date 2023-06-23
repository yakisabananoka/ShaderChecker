#include <DxLib.h>
#include "Application.h"
#include "Scene/SceneManager.h"
#include "Graphics/Drawable/Screen.h"

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
	SetWindowText("ShaderChecker");				//ウィンドウタイトルの設定
	SetGraphMode(1024, 768, 32);				//ウィンドウサイズの設定
	SetOutApplicationLogValidFlag(false);		//ログファイルの出力無効化
	ChangeWindowMode(true);						//ウィンドウモードに変更
	SetUseDirect3D11(true);						//DirectX11を使用

	//DXライブラリを初期化
	if(DxLib_Init() == -1)
	{
		return false;
	}
	
	SetUseZBuffer3D(true);			//Zバッファを使用
	SetWriteZBuffer3D(true);		//Zバッファに書き込み

	return true;					//DXライブラリ初期化処理
}

void Application::Update(void)
{
	SceneManager sceneManager;

	//DXライブラリ側で異常を検知した場合かエスケープキーを押下した際にゲームループを出る
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		sceneManager.Update();	//シーンマネージャーの更新
		Screen::Flip();			//実際の画面に反映
	}
}
