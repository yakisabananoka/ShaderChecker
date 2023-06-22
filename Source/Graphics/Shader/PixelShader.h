#pragma once
#include <filesystem>
#include "Shader.h"

/// @brief ピクセルシェーダー
class PixelShader final :
	public Shader
{
public:
	/// @brief 生成関数
	/// @param path ファイルパス
	/// @return ピクセルシェーダー
	static PixelShaderPtr Create(const std::filesystem::path& path);

	~PixelShader() override = default;

	/// @brief 開始処理
	void Begin(void) const;

	/// @brief 終了処理
	void End(void) const;

	/// @brief マルチレンダーターゲット用の描き込み対象の設定(基本2D用)
	/// @param renderTargets レンダーターゲットの管理オブジェクト
	void SetRenderTargets(RenderTargetsWeakPtr renderTargets);

	/// @brief マルチレンダーターゲット用の描き込み対象の設定(基本3D用)
	/// @param renderTargets レンダーターゲットの管理オブジェクト
	/// @param camera カメラ
	void SetRenderTargets(RenderTargetsWeakPtr renderTargets, CameraWeakPtr camera);

	/// @brief 任意で転送する画像を設定
	/// @param image 画像
	/// @param slot スロット番号(0以降)
	void SetTexture(ImageWeakPtr image, int slot);

	/// @brief nullptrを設定すると画像を解除する
	/// @param slot スロット番号
	void SetTexture(nullptr_t, int slot);

	PixelShader(const PixelShader&) = delete;
	PixelShader& operator=(const PixelShader&) = delete;

	PixelShader(PixelShader&&) = delete;
	PixelShader& operator=(PixelShader&&) = delete;

private:
	/// @brief コンストラクタ
	/// @param path ファイルパス
	PixelShader(const std::filesystem::path& path);

	/// @brief レンダーターゲットの開始処理
	void BeginRenderTarget(void) const;

	/// @brief レンダーターゲットの終了処理
	void EndRenderTarget(void) const;

	/// @brief テクスチャの開始処理
	void BeginTexture(void) const;

	/// @brief テクスチャの終了処理
	void EndTexture(void) const;

	RenderTargetsWeakPtr renderTargets_;					//レンダーターゲットの管理オブジェクト
	CameraWeakPtr camera_;									//カメラの弱参照
	std::unordered_map<int, ImageWeakPtr> textureInfo_;		//テクスチャの弱参照を保持するハッシュマップ

};
