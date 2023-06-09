﻿#pragma once
#include <filesystem>
#include <DxLib.h>
#include "Graphics/UsingGraphics.h"

/// @brief 画像
class Image
{
public:
	/// @brief Imageの生成関数(出力型を限定するため)
	/// @param path ファイルパス
	/// @return Imageのshared_ptr
	static ImagePtr Create(const std::filesystem::path& path);

	virtual ~Image();

	/// @brief シェーダーに対して設定
	/// @param slot スロット番号(0以降)
	void SetupToShader(int slot) const;

	/// @brief 通常の描画
	/// @param x X座標
	/// @param y Y座標
	/// @param transFlg 透過するか
	void Draw(float x, float y, bool transFlg) const;

	/// @brief 拡大縮小を伴う描画
	/// @param x1 左上のX座標
	/// @param y1 左上のY座標
	/// @param x2 右下のX座標
	/// @param y2 右下のY座標
	/// @param transFlg 透過するか
	void Draw(float x1, float y1, float x2, float y2, bool transFlg) const;

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
	void Draw(VECTOR pos, float cx, float cy, float size, float angle, bool transFlg) const;

	/// @brief シェーダーを使用したビルボードとしての描画
	/// @param pos 位置
	/// @param cx 中心X座標
	/// @param cy 中心Y座標
	/// @param size サイズ
	/// @param angle 回転角度(ラジアン)
	/// @param transFlg 透過するか
	/// @param pixel ピクセルシェーダー
	void Draw(VECTOR pos, float cx, float cy, float size, float angle, bool transFlg, const PixelShader& pixel) const;

	Image(const Image&) = delete;
	Image& operator=(const Image&) = delete;

	Image(Image&& image) = delete;
	Image& operator=(Image&& image) = delete;
protected:
	/// @brief コンストラクタ
	/// @param handle ハンドル
	Image(int handle);

	int handle_;		//ハンドル

private:
	/// @brief コンストラクタ
	/// @param path ファイルパス
	Image(const std::filesystem::path& path);
};

