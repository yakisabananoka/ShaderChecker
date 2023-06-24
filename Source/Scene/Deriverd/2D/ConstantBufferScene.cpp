#include "ConstantBufferScene.h"
#include "Graphics/Drawable/Image.h"
#include "Graphics/Drawable/Screen.h"
#include "Graphics/Shader/ConstantBuffer.h"
#include "Graphics/Shader/PixelShader.h"

ScenePtrTemplate<ConstantBufferScene> ConstantBufferScene::Create(void)
{
	return ScenePtrTemplate<ConstantBufferScene>(new ConstantBufferScene());
}

ConstantBufferScene::~ConstantBufferScene() = default;

void ConstantBufferScene::Update(void)
{
	constantBuffer_->GetValue().time = stopWatch_.GetNowCount();		//CPU側に確保されたバッファに経過時間を書き込み
	constantBuffer_->Update();											//CPU→GPUにバッファを転送

	//ここから描画処理

	screen_->Setup();		//スクリーンの設定
	screen_->Clear();		//スクリーンを初期化

	image_->Draw(0.0f, 0.0f, *pixelShader_);		//ピクセルシェーダーを使用して画像を描画

	//ここまで描画処理
}

ConstantBufferScene::ConstantBufferScene() :
	Scene("定数バッファを使ったシーン"),
	image_(Image::Create("Assets/Image/texture0.png")),
	pixelShader_(PixelShader::Create("Assets/ShaderBinary/Pixel/UseConstantBufferShader.pso")),
	constantBuffer_(ConstantBuffer<Test>::Create())
{
	pixelShader_->SetConstantBuffer(constantBuffer_, 3);			//ピクセルシェーダーの3番スロットに定数バッファをセット
	stopWatch_.Start();												//計測開始
}
