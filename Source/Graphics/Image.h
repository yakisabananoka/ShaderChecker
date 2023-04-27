#pragma once
#include <filesystem>
#include "UsingGraphics.h"

/// @brief 画像
class Image
{
public:
	/// @brief コンストラクタ
	/// @param path ファイルパス
	Image(const std::filesystem::path& path);
	~Image();

	/// @brief 通常の描画
	/// @param x X座標
	/// @param y Y座標
	/// @param transFlg 透過するか
	void Draw(float x, float y, bool transFlg) const;

	/// @brief シェーダーを使用した描画
	/// @param x X座標
	/// @param y Y座標
	/// @param pixelShader ピクセルシェーダー
	void Draw(float x, float y, const PixelShader& pixelShader) const;

	Image(const Image&) = delete;
	Image& operator=(const Image&) = delete;

	Image(Image&&) = default;
	Image& operator=(Image&&) = default;

private:
	int handle_;		//ハンドル
};

