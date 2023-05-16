#pragma once
#include <memory>

class ConstantBufferBase;
class VertexShader;
class PixelShader;
class Camera;

using ConstantBufferBaseWeakPtr = std::weak_ptr<ConstantBufferBase>;		//ConstantBufferBaseの弱参照
