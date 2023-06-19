#pragma once
#include <filesystem>
#include <DxLib.h>
#include "Graphics/UsingGraphics.h"

/// @brief モデル
class Model
{
public:
	/// @brief コンストラクタ
	/// @param path ファイルパス
	Model(const std::filesystem::path& path);
	~Model();

	/// @brief 位置の設定
	/// @param x X座標
	/// @param y Y座標
	/// @param z Z座標
	void SetPosition(float x, float y, float z);

	/// @brief 位置の設定
	/// @param pos 位置座標
	void SetPosition(const VECTOR& pos);

	/// @brief 回転の設定
	/// @param x X回転
	/// @param y Y回転
	/// @param z Z回転
	void SetRotation(float x, float y, float z);

	/// @brief 回転の設定
	/// @param rot 回転量
	void SetRotation(const VECTOR& rot);

	/// @brief 描画
	void Draw(void) const;

	/// @brief シェーダーを利用した描画
	/// @param vertex 頂点シェーダー
	/// @param pixel ピクセルシェーダー
	void Draw(const VertexShader& vertex, const PixelShader& pixel) const;

	Model(const Model& model);
	Model& operator=(const Model& model);

	Model(Model&& model) noexcept;
	Model& operator=(Model&& model) noexcept;

private:
	int handle_;		//ハンドル
};
