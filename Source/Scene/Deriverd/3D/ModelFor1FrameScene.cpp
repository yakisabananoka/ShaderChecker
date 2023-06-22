#include "ModelFor1FrameScene.h"
#include "Graphics/Drawable/Screen.h"
#include "Graphics/Drawable/Model.h"
#include "Graphics/Shader/VertexShader.h"
#include "Graphics/Shader/PixelShader.h"
#include "Graphics/Camera/PerspectiveCamera.h"

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
	camera_->Setup();			//カメラのセット
	
	model_->Draw(*vertexShader_, *pixelShader_);				//シェーダーを利用したモデルの描画

	//ここまで描画処理
}

ModelFor1FrameScene::ModelFor1FrameScene(
	const std::filesystem::path& modelPath,
	const std::filesystem::path& vertexShaderPath,
	const std::filesystem::path& pixelShaderPath) :
	model_(Model::Create(modelPath)), camera_(PerspectiveCamera::Create()), vertexShader_(VertexShader::Create(vertexShaderPath)), pixelShader_(PixelShader::Create(pixelShaderPath))
{
	camera_->SetPosition({ -300.0f,300.0f,-300.0f });		//カメラの位置を設定
}
