#include "ModelForAllFrameScene.h"
#include "Graphics/Camera/PerspectiveCamera.h"
#include "Graphics/Drawable/Screen.h"
#include "Graphics/Drawable/Model.h"
#include "Graphics/Shader/PixelShader.h"
#include "Graphics/Shader/VertexShader.h"

ScenePtrTemplate<ModelForAllFrameScene> ModelForAllFrameScene::Create(
	const std::string& name,
	const std::filesystem::path& modelPath,
	const std::filesystem::path& vertex1FrameShaderPath,
	const std::filesystem::path& vertex4FrameShaderPath,
	const std::filesystem::path& vertex8FrameShaderPath,
	const std::filesystem::path& pixelShaderPath)
{
	return ScenePtrTemplate<ModelForAllFrameScene>(new ModelForAllFrameScene(name, modelPath, vertex1FrameShaderPath, vertex4FrameShaderPath, vertex8FrameShaderPath, pixelShaderPath));
}

void ModelForAllFrameScene::Update(void)
{
	//回転処理
	auto rot = model_->GetRotation();
	rot.y += 0.01f;

	model_->SetRotation(rot);

	//ここから描画処理

	screen_->Setup();			//スクリーンをセット
	screen_->Clear();			//スクリーンを初期化
	camera_->Setup();			//カメラのセット

	model_->Draw(*vertex1FrameShader_, *vertex4FrameShader_, *vertex8FrameShader_, *pixelShader_);		//シェーダーを利用したモデルの描画

	//ここまで描画処理
}

ModelForAllFrameScene::ModelForAllFrameScene(
	const std::string& name,
	const std::filesystem::path& modelPath,
	const std::filesystem::path& vertex1FrameShaderPath,
	const std::filesystem::path& vertex4FrameShaderPath,
	const std::filesystem::path& vertex8FrameShaderPath,
	const std::filesystem::path& pixelShaderPath) :
	Scene(name),
	model_(Model::Create(modelPath)), camera_(PerspectiveCamera::Create()),
	vertex1FrameShader_(VertexShader::Create(vertex1FrameShaderPath)),
	vertex4FrameShader_(VertexShader::Create(vertex4FrameShaderPath)),
	vertex8FrameShader_(VertexShader::Create(vertex8FrameShaderPath)),
	pixelShader_(PixelShader::Create(pixelShaderPath))
{
	camera_->SetPosition({ -300.0f,300.0f,-300.0f });		//カメラの位置を設定

	model_->SetPosition(0.0f, -150.0f, 0.0f);		//モデルの位置を設定
	model_->SetScale(2.0f, 2.0f, 2.0f);				//モデルの拡大率を設定
}
