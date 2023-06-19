#pragma once
#include <memory>

class Image;
class Screen;
class ConstantBufferBase;
template<typename T>
	requires(sizeof(T) % 16 == 0)
class ConstantBuffer;
class VertexShader;
class PixelShader;
class Camera;

template<typename T>
using ImagePtrTemplate = std::shared_ptr<T>;
template<typename T>
using ImageWeakPtrTemplate = std::weak_ptr<T>;

using ImagePtr = ImagePtrTemplate<Image>;
using ImageWeakPtr = ImageWeakPtrTemplate<Image>;

using ScreenPtr = ImagePtrTemplate<Screen>;
using ScreenWeakPtr = ImageWeakPtrTemplate<Screen>;

template<typename T>
	requires(sizeof(T) % 16 == 0)
using ConstantBufferPtr = std::shared_ptr<ConstantBuffer<T>>;

using ConstantBufferBaseWeakPtr = std::weak_ptr<ConstantBufferBase>;		//ConstantBufferBaseの弱参照
