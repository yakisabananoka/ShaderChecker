#pragma once
#include "Scene/Scene.h"
#include "Scene/UsingScene.h"
#include "Graphics/Drawable/Model.h"
#include "Graphics/Shader/VertexShader.h"
#include "Graphics/Shader/PixelShader.h"
#include "Graphics/Camera/PerspectiveCamera.h"

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

	Model model_;					//モデル
	PerspectiveCamera camera_;		//カメラ

	VertexShader vertexShader_;		//頂点シェーダー
	PixelShader pixelShader_;		//ピクセルシェーダー
};
