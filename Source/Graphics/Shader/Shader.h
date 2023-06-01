#pragma once
#include <unordered_map>
#include "Graphics/UsingGraphics.h"

/// @brief シェーダー
class Shader
{
public:
	/// @brief コンストラクタ
	/// @param handle ハンドル
	Shader(int handle);
	virtual ~Shader();

	/// @brief 定数バッファの設定
	/// @param ptr 定数バッファの基底の弱参照
	/// @param slot スロット番号
	void SetConstantBuffer(ConstantBufferBaseWeakPtr ptr, int slot);

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

	Shader(Shader&& shader) noexcept;
	Shader& operator=(Shader&& shader) noexcept;

protected:
	/// @brief 定数バッファの開始処理
	/// @param shaderType シェーダーの種類(DXライブラリ定義)
	void BeginConstantBuffer(int shaderType) const;

	/// @brief 定数バッファの終了処理
	/// @param shaderType シェーダーの種類(DXライブラリ定義)
	void EndConstantBuffer(int shaderType) const;

	std::unordered_map<int, ConstantBufferBaseWeakPtr> constantBufferInfos_;		//定数バッファの弱参照を保持するハッシュマップ
	int handle_;		//ハンドル
};
