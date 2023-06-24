#pragma once
#include <filesystem>
#include "Scene/Scene.h"
#include "Scene/UsingScene.h"
#include "Graphics/UsingGraphics.h"

class MultiRenderTargetScene final :
	public Scene
{
public:
	/// @brief MultiRenderTargetSceneの生成
	///	@param name シーン名
	/// @param imagePath 画像のファイルパス
	/// @param pixelShaderPath ピクセルシェーダーのパス
	/// @param num レンダーターゲットの数(ピクセルシェーダーの出力数に合わせる)
	/// @return 生成されたMultiRenderTargetScene
	static ScenePtrTemplate<MultiRenderTargetScene> Create(const std::string& name, const std::filesystem::path& imagePath, const std::filesystem::path& pixelShaderPath, unsigned int num);

	/// @brief デストラクタ
	~MultiRenderTargetScene() override;

	/// @brief 更新
	void Update(void) override;

	MultiRenderTargetScene(const MultiRenderTargetScene&) = delete;
	MultiRenderTargetScene& operator=(const MultiRenderTargetScene&) = delete;

	MultiRenderTargetScene(MultiRenderTargetScene&&) = delete;
	MultiRenderTargetScene& operator=(MultiRenderTargetScene&&) = delete;
private:
	MultiRenderTargetScene(const std::string& name, const std::filesystem::path& imagePath, const std::filesystem::path& pixelShaderPath, unsigned int num);

	ImagePtr image_;					//画像
	PixelShaderPtr pixelShader_;		//画像用のピクセルシェーダー
	RenderTargetsPtr renderTargets_;	//レンダーターゲットの管理オブジェクト
};
