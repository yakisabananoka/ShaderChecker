#pragma once
#include <filesystem>
#include <DxLib.h>
#include "Graphics/UsingGraphics.h"

/// @brief 画像
class Image
{
public:
	/// @brief コンストラクタ
	/// @param path ファイルパス
	Image(std::filesystem::path path);

	virtual ~Image();

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

	/// @brief ビルボードとしての描画
	/// @param pos 位置
	/// @param cx 中心X座標
	/// @param cy 中心Y座標
	/// @param size サイズ
	/// @param angle 回転角度(ラジアン)
	/// @param transFlg 透過するか
	void Draw(VECTOR pos, float cx, float cy, float size, float angle, bool transFlg);

	/// @brief シェーダーを使用したビルボードとしての描画
	/// @param pos 位置
	/// @param cx 中心X座標
	/// @param cy 中心Y座標
	/// @param size サイズ
	/// @param angle 回転角度(ラジアン)
	/// @param transFlg 透過するか
	/// @param pixel ピクセルシェーダー
	void Draw(VECTOR pos, float cx, float cy, float size, float angle, bool transFlg, const PixelShader& pixel);

	Image(const Image&) = delete;
	Image& operator=(const Image&) = delete;

	Image(Image&& image) noexcept;
	Image& operator=(Image&& image) noexcept;
protected:
	/// @brief コンストラクタ
	/// @param handle ハンドル
	Image(int handle);

	int handle_;		//ハンドル
};

