#pragma once
#include <filesystem>
#include "Scene/Scene.h"
#include "Scene/UsingScene.h"
#include "Graphics/UsingGraphics.h"

class ModelForAllFrameScene final :
	public Scene
{
public:
	/// @brief 生成関数
	/// @param modelPath モデルのファイルパス
	/// @param vertex1FrameShaderPath 頂点シェーダー(1フレーム)のファイルパス
	/// @param vertex4FrameShaderPath 頂点シェーダー(1～4フレーム)のファイルパス
	/// @param vertex8FrameShaderPath 頂点シェーダー(5～8フレーム)のファイルパス
	/// @param pixelShaderPath ピクセルシェーダーのファイルパス
	/// @return 生成されたModelForAllFrameScene
	static ScenePtrTemplate<ModelForAllFrameScene> Create(
		const std::filesystem::path& modelPath,
		const std::filesystem::path& vertex1FrameShaderPath,
		const std::filesystem::path& vertex4FrameShaderPath,
		const std::filesystem::path& vertex8FrameShaderPath,
		const std::filesystem::path& pixelShaderPath);

	~ModelForAllFrameScene()override = default;

	/// @brief 更新
	void Update(void) override;

	ModelForAllFrameScene(const ModelForAllFrameScene&) = delete;
	ModelForAllFrameScene& operator=(const ModelForAllFrameScene&) = delete;

	ModelForAllFrameScene(ModelForAllFrameScene&&) = delete;
	ModelForAllFrameScene& operator=(ModelForAllFrameScene&&) = delete;

private:
	ModelForAllFrameScene(
		const std::filesystem::path& modelPath,
		const std::filesystem::path& vertex1FrameShaderPath,
		const std::filesystem::path& vertex4FrameShaderPath,
		const std::filesystem::path& vertex8FrameShaderPath,
		const std::filesystem::path& pixelShaderPath);

	ModelPtr model_;						//モデル
	PerspectiveCameraPtr camera_;			//カメラ

	VertexShaderPtr vertex1FrameShader_;	//頂点シェーダー(1フレーム)
	VertexShaderPtr vertex4FrameShader_;	//頂点シェーダー(1～4フレーム)
	VertexShaderPtr vertex8FrameShader_;	//頂点シェーダー(5～8フレーム)
	
	PixelShaderPtr pixelShader_;			//ピクセルシェーダー
};
