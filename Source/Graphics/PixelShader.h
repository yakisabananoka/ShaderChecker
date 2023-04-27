#pragma once
#include <filesystem>
#include "Shader.h"

/// @brief ピクセルシェーダー
class PixelShader :
	public Shader
{
public:
	/// @brief コンストラクタ
	/// @param path ファイルパス
	PixelShader(std::filesystem::path path);
	~PixelShader() override;

	/// @brief 開始処理
	void Begin(void) const;

	/// @brief 終了処理
	void End(void) const;

	PixelShader(const PixelShader&) = delete;
	PixelShader& operator=(const PixelShader&) = delete;

	PixelShader(PixelShader&&) = default;
	PixelShader& operator=(PixelShader&&) = default;

private:
	int handle_;		//ハンドル

};
