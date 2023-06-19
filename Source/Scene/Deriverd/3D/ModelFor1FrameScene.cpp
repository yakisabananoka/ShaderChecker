#include "ModelFor1FrameScene.h"
#include "Graphics/Drawable/Screen.h"

ScenePtrTemplate<ModelFor1FrameScene> ModelFor1FrameScene::Create(
	const std::filesystem::path& modelPath,
	const std::filesystem::path& vertexShaderPath,
	const std::filesystem::path& pixelShaderPath)
{
	return ScenePtrTemplate<ModelFor1FrameScene>(new ModelFor1FrameScene(modelPath, vertexShaderPath, pixelShaderPath));
}

void ModelFor1FrameScene::Update(void)
{
	//ここから描画処理

	screen_->Setup();			//スクリーンをセット
	screen_->Clear();			//スクリーンを初期化
	camera_.Setup();			//カメラのセット

	model_.Draw(vertexShader_, pixelShader_);				//シェーダーを利用したモデルの描画

	//ここまで描画処理
}

ModelFor1FrameScene::ModelFor1FrameScene(
	const std::filesystem::path& modelPath,
	const std::filesystem::path& vertexShaderPath,
	const std::filesystem::path& pixelShaderPath) :
	model_(modelPath), vertexShader_(vertexShaderPath), pixelShader_(pixelShaderPath)
{
	camera_.SetPosition({ -300.0f,300.0f,-300.0f });		//カメラの位置を設定
}
