#pragma once
#include <DxLib.h>
#include "../ConstantBuffer.h"

template <class T>
	requires (sizeof(T) % 16 == 0)
ConstantBuffer<T>::ConstantBuffer()
{
	handle_ = CreateShaderConstantBuffer(sizeof(T));		//定数バッファの生成
}

template <class T>
	requires (sizeof(T) % 16 == 0)
ConstantBuffer<T>::~ConstantBuffer()
{
	DeleteShaderConstantBuffer(handle_);					//定数バッファの削除
}

template <class T>
	requires (sizeof(T) % 16 == 0)
const int& ConstantBuffer<T>::GetHandle(void) const
{
	return handle_;
}

template <class T>
	requires (sizeof(T) % 16 == 0)
T& ConstantBuffer<T>::GetValue(void)
{
	return *static_cast<T*>(GetBufferShaderConstantBuffer(handle_));		//void*→T&に変換(直接変換不可なので一度ポインタにする)
}

template <class T>
	requires (sizeof(T) % 16 == 0)
void ConstantBuffer<T>::Update(void) const
{
	UpdateShaderConstantBuffer(handle_);		//更新
}

template <class T>
	requires (sizeof(T) % 16 == 0)
ConstantBuffer<T>::ConstantBuffer(ConstantBuffer&& constantBuffer) noexcept :
	handle_(constantBuffer.handle_)
{
	constantBuffer.handle_ = -1;
}

template <class T>
	requires (sizeof(T) % 16 == 0)
ConstantBuffer<T>& ConstantBuffer<T>::operator=(ConstantBuffer&& constantBuffer) noexcept
{
	handle_ = constantBuffer.handle_;
	constantBuffer.handle_ = -1;
	return *this;
}

