#pragma once
#include <memory>

class ConstantBufferBase;
class PixelShader;

template<class T>
class ConstantBuffer;

template<class T>
using ConstantBufferPtr = ConstantBuffer<T>;
using ConstantBufferBaseWeakPtr = std::weak_ptr<ConstantBufferBase>;

