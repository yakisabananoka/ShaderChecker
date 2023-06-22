#pragma once
#include "Graphics/UsingGraphics.h"

/// @brief 定数バッファの基底クラス
class ConstantBufferBase
{
public:
	ConstantBufferBase() = default;
	virtual ~ConstantBufferBase() = default;

	/// @brief シェーダーの使用設定
	/// @param slot スロット番号
	/// @param shaderType シェーダーの種類
	virtual void Setup(int slot, int shaderType) const = 0;

	ConstantBufferBase(const ConstantBufferBase&) = delete;
	ConstantBufferBase& operator=(const ConstantBufferBase&) = delete;

	ConstantBufferBase(ConstantBufferBase&&) = delete;
	ConstantBufferBase& operator=(ConstantBufferBase&&) = delete;

};

/// @brief 定数バッファ
/// @tparam T 転送したい値の型(型のサイズを16の倍数にする必要アリ)
template<class T>
	requires (sizeof(T)%16 == 0)
class ConstantBuffer final :
	public ConstantBufferBase
{
public:
	static ConstantBufferPtr<T> Create(void);

	~ConstantBuffer() override;

	/// @brief 値の取得
	/// @return 値の参照
	[[nodiscard]]
	T& GetValue(void);

	/// @brief 更新(値を変更した後は必ず行う)
	void Update(void) const;

	/// @brief シェーダーの使用設定
	/// @param slot スロット番号
	/// @param shaderType シェーダーの種類
	void Setup(int slot, int shaderType) const override;

	ConstantBuffer(const ConstantBuffer&) = delete;
	ConstantBuffer& operator=(const ConstantBuffer&) = delete;

	ConstantBuffer(ConstantBuffer&&) = delete;
	ConstantBuffer& operator=(ConstantBuffer&&) = delete;

private:
	ConstantBuffer();

	int handle_;		//ハンドル
};

#include "Details/ConstantBuffer.h"
