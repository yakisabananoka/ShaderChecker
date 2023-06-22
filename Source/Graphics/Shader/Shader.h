#pragma once
#include <unordered_map>
#include "Graphics/UsingGraphics.h"

/// @brief シェーダー
class Shader
{
public:
	virtual ~Shader();

	/// @brief 定数バッファの設定
	/// @param ptr 定数バッファの基底の弱参照
	/// @param slot スロット番号(0以降)
	void SetConstantBuffer(ConstantBufferBaseWeakPtr ptr, int slot);

	/// @brief nullptrを設定すると定数バッファの解除を行う
	/// @param slot スロット番号(0以降)
	void SetConstantBuffer(nullptr_t, int slot);

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

	Shader(Shader&&) = delete;
	Shader& operator=(Shader&&) = delete;

protected:
	/// @brief コンストラクタ
	/// @param handle ハンドル
	Shader(int handle);

	/// @brief 定数バッファの開始処理
	/// @param shaderType シェーダーの種類(DXライブラリ定義)
	void BeginConstantBuffer(int shaderType) const;

	/// @brief 定数バッファの終了処理
	/// @param shaderType シェーダーの種類(DXライブラリ定義)
	void EndConstantBuffer(int shaderType) const;

	int handle_;		//ハンドル

private:
	std::unordered_map<int, ConstantBufferBaseWeakPtr> constantBufferInfo_;		//定数バッファの弱参照を保持するハッシュマップ
};
