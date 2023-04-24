#pragma once
#include <DxLib.h>
#include "../ConstantBuffer.h"

template <class T>
ConstantBuffer<T>::ConstantBuffer()
{
	handle_ = CreateShaderConstantBuffer(sizeof(T));
}

template <class T>
ConstantBuffer<T>::~ConstantBuffer()
{
	DeleteShaderConstantBuffer(handle_);
}

template <class T>
const int& ConstantBuffer<T>::GetHandle(void) const
{
	return handle_;
}

template <class T>
T& ConstantBuffer<T>::GetValue(void)
{
	return *static_cast<T*>(GetBufferShaderConstantBuffer(handle_));
}

template <class T>
void ConstantBuffer<T>::Update(void)
{
	UpdateShaderConstantBuffer(handle_);
}

