#pragma once
#include <filesystem>
#include "Scene/Scene.h"
#include "Scene/UsingScene.h"
#include "Graphics/UsingGraphics.h"

class ImageScene final:
	public Scene
{
public:
	/// @brief ImageSceneの生成
	/// @return 生成されたImageScene
	static ScenePtrTemplate<ImageScene> Create(const std::filesystem::path& imagePath, const std::filesystem::path& pixelShaderPath);

	/// @brief デストラクタ
	~ImageScene() override;

	/// @brief 更新
	void Update(void) override;

	ImageScene(const ImageScene&) = delete;
	ImageScene& operator=(const ImageScene&) = delete;

	ImageScene(ImageScene&&) = delete;
	ImageScene& operator=(ImageScene&&) = delete;
private:
	ImageScene(const std::filesystem::path& imagePath, const std::filesystem::path& pixelShaderPath);

	ImagePtr image_;					//画像
	PixelShaderPtr pixelShader_;		//画像用のピクセルシェーダー
};
