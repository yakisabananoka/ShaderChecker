#pragma once
#include <filesystem>
#include "Scene/Scene.h"
#include "Scene/UsingScene.h"
#include "Graphics/UsingGraphics.h"

class ModelFor1FrameScene final:
	public Scene
{
public:
	static ScenePtrTemplate<ModelFor1FrameScene> Create(
		const std::filesystem::path& modelPath,
		const std::filesystem::path& vertexShaderPath,
		const std::filesystem::path& pixelShaderPath);

	~ModelFor1FrameScene()override = default;

	void Update(void) override;

	ModelFor1FrameScene(const ModelFor1FrameScene&) = delete;
	ModelFor1FrameScene& operator=(const ModelFor1FrameScene&) = delete;

	ModelFor1FrameScene(ModelFor1FrameScene&&) = delete;
	ModelFor1FrameScene& operator=(ModelFor1FrameScene&&) = delete;

private:
	ModelFor1FrameScene(
		const std::filesystem::path& modelPath,
		const std::filesystem::path& vertexShaderPath,
		const std::filesystem::path& pixelShaderPath);

	ModelPtr model_;					//モデル
	PerspectiveCameraPtr camera_;		//カメラ

	VertexShaderPtr vertexShader_;		//頂点シェーダー
	PixelShaderPtr pixelShader_;		//ピクセルシェーダー
};
