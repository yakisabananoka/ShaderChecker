#pragma once
#include <DxLib.h>
#include "../ConstantBuffer.h"

template <class T>
ConstantBuffer<T>::ConstantBuffer()
{
	handle_ = CreateShaderConstantBuffer(sizeof(T));		//定数バッファの生成
}

template <class T>
ConstantBuffer<T>::~ConstantBuffer()
{
	DeleteShaderConstantBuffer(handle_);					//定数バッファの削除
}

template <class T>
const int& ConstantBuffer<T>::GetHandle(void) const
{
	return handle_;
}

template <class T>
T& ConstantBuffer<T>::GetValue(void)
{
	return *static_cast<T*>(GetBufferShaderConstantBuffer(handle_));		//void*→T&に変換(直接変換不可なので一度ポインタにする)
}

template <class T>
void ConstantBuffer<T>::Update(void)
{
	UpdateShaderConstantBuffer(handle_);		//更新
}

