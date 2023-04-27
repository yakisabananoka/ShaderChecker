#pragma once

/// @brief 定数バッファの基底クラス
class ConstantBufferBase
{
public:
	ConstantBufferBase() = default;
	virtual ~ConstantBufferBase() = default;

	/// @brief ハンドルの取得
	/// @return ハンドルの参照
	[[nodiscard]]
	virtual const int& GetHandle(void)const = 0;

	ConstantBufferBase(const ConstantBufferBase&) = delete;
	ConstantBufferBase& operator=(const ConstantBufferBase&) = delete;

	ConstantBufferBase(ConstantBufferBase&&) = default;
	ConstantBufferBase& operator=(ConstantBufferBase&&) = default;

};

/// @brief 定数バッファ
/// @tparam T 転送したい値の型(型のサイズを16の倍数にする必要アリ)
template<class T>
class ConstantBuffer :
	public ConstantBufferBase
{
public:
	ConstantBuffer();
	~ConstantBuffer() override;

	/// @brief ハンドルの取得
	/// @return ハンドル
	[[nodiscard]]
	const int& GetHandle(void)const override;

	/// @brief 値の取得
	/// @return 値の参照
	[[nodiscard]]
	T& GetValue(void);

	/// @brief 更新(値を変更した後は必ず行う)
	void Update(void);

	ConstantBuffer(const ConstantBuffer&) = delete;
	ConstantBuffer& operator=(const ConstantBuffer&) = delete;

	ConstantBuffer(ConstantBuffer&&) = default;
	ConstantBuffer& operator=(ConstantBuffer&&) = default;

private:
	int handle_;		//ハンドル
};

#include "Details/ConstantBuffer.h"