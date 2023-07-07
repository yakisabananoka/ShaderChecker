#pragma once
#include <memory>

class Image;
class Screen;

class Model;

class ConstantBufferBase;
template<typename T>
	requires(sizeof(T) % 16 == 0)
class ConstantBuffer;

class RenderTargets;

class Shader;
class VertexShader;
class PixelShader;

class Camera;
class PerspectiveCamera;

class Material;

template<typename T>
using ImagePtrTemplate = std::shared_ptr<T>;
template<typename T>
using ImageWeakPtrTemplate = std::weak_ptr<T>;

using ImagePtr = ImagePtrTemplate<Image>;
using ImageWeakPtr = ImageWeakPtrTemplate<Image>;

using ScreenPtr = ImagePtrTemplate<Screen>;
using ScreenWeakPtr = ImageWeakPtrTemplate<Screen>;

template<typename T>
using ModelPtrTemplate = std::shared_ptr<T>;
template<typename T>
using ModelWeakPtrTemplate = std::weak_ptr<T>;

using ModelPtr = ModelPtrTemplate<Model>;
using ModelWeakPtr = ModelWeakPtrTemplate<Model>;

template<typename T>
	requires(sizeof(T) % 16 == 0)
using ConstantBufferPtr = std::shared_ptr<ConstantBuffer<T>>;

using ConstantBufferBaseWeakPtr = std::weak_ptr<ConstantBufferBase>;		//ConstantBufferBaseの弱参照

template<typename T>
using RenderTargetsPtrTemplate = std::shared_ptr<T>;
template<typename T>
using RenderTargetsWeakPtrTemplate = std::weak_ptr<T>;

using RenderTargetsPtr = RenderTargetsPtrTemplate<RenderTargets>;
using RenderTargetsWeakPtr = RenderTargetsWeakPtrTemplate<RenderTargets>;

template<typename T>
using ShaderPtrTemplate = std::shared_ptr<T>;
template<typename T>
using ShaderWeakPtrTemplate = std::weak_ptr<T>;

using ShaderPtr = ShaderPtrTemplate<Shader>;
using ShaderWeakPtr = ShaderWeakPtrTemplate<Shader>;

using VertexShaderPtr = ShaderPtrTemplate<VertexShader>;
using VertexShaderWeakPtr = ShaderWeakPtrTemplate<VertexShader>;

using PixelShaderPtr = ShaderPtrTemplate<PixelShader>;
using PixelShaderWeakPtr = ShaderWeakPtrTemplate<PixelShader>;

template<typename T>
using CameraPtrTemplate = std::shared_ptr<T>;
template<typename T>
using CameraWeakPtrTemplate = std::weak_ptr<T>;

using CameraPtr = CameraPtrTemplate<Camera>;
using CameraWeakPtr = CameraWeakPtrTemplate<Camera>;
using PerspectiveCameraPtr = CameraPtrTemplate<PerspectiveCamera>;

template<typename T>
using MaterialPtrTemplate = std::shared_ptr<T>;
template<typename T>
using MaterialWeakPtrTemplate = std::weak_ptr<T>;

using MaterialPtr = MaterialPtrTemplate<Material>;
using MaterialWeakPtr = MaterialWeakPtrTemplate<Material>;
