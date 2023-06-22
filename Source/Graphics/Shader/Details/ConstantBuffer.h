#pragma once
#include <DxLib.h>
#include "../ConstantBuffer.h"

template <class T>
	requires (sizeof(T) % 16 == 0)
ConstantBufferPtr<T> ConstantBuffer<T>::Create(void)
{
	return ConstantBufferPtr<T>(new ConstantBuffer);
}

template <class T>
	requires (sizeof(T) % 16 == 0)
ConstantBuffer<T>::~ConstantBuffer()
{
	DeleteShaderConstantBuffer(handle_);					//定数バッファの削除
}

template <class T>
	requires (sizeof(T) % 16 == 0)
T& ConstantBuffer<T>::GetValue(void)
{
	return *static_cast<T*>(GetBufferShaderConstantBuffer(handle_));		//void* -> T&に変換(直接変換不可なので一度ポインタにする)
}

template <class T>
	requires (sizeof(T) % 16 == 0)
void ConstantBuffer<T>::Update(void) const
{
	UpdateShaderConstantBuffer(handle_);		//更新
}

template <class T>
	requires (sizeof(T) % 16 == 0)
void ConstantBuffer<T>::Setup(int slot, int shaderType) const
{
	SetShaderConstantBuffer(handle_, shaderType, slot);
}

template <class T>
	requires (sizeof(T) % 16 == 0)
ConstantBuffer<T>::ConstantBuffer()
{
	handle_ = CreateShaderConstantBuffer(sizeof(T));		//定数バッファの生成
}
