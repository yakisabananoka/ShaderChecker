#pragma once
#include <filesystem>
#include "Shader.h"

/// @brief 頂点シェーダー
class VertexShader final :
	public Shader
{
public:
	/// @brief コンストラクタ
	/// @param path ファイルパス
	VertexShader(std::filesystem::path path);
	~VertexShader() override = default;

	/// @brief 開始処理
	void Begin(void) const;

	/// @brief 終了処理
	void End(void) const;

	VertexShader(const VertexShader&) = delete;
	VertexShader& operator=(const VertexShader&) = delete;

	VertexShader(VertexShader&&) = default;
	VertexShader& operator=(VertexShader&&) = default;
};
