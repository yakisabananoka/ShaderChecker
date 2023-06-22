#include <ranges>
#include <DxLib.h>
#include "Shader.h"
#include "ConstantBuffer.h"

Shader::~Shader()
{
	DeleteShader(handle_);
}

void Shader::SetConstantBuffer(ConstantBufferBaseWeakPtr ptr, int slot)
{
	constantBufferInfo_[slot] = std::move(ptr);		//スロット番号をキーとしてハッシュマップに保持
}

void Shader::SetConstantBuffer(nullptr_t, int slot)
{
	if (constantBufferInfo_.contains(slot))
	{
		constantBufferInfo_.erase(slot);
	}
}

Shader::Shader(int handle) :
	handle_(handle)
{
}

void Shader::BeginConstantBuffer(int shaderType) const
{
	//設定された全定数バッファの取り出し
	for (const auto& [slot, ptr] : constantBufferInfo_)
	{
		//定数バッファが生きている場合はロック
		if (const auto constantBufferPtr = ptr.lock())
		{
			constantBufferPtr->Setup(slot, shaderType);		//シェーダーに対して定数バッファのハンドルをセット
		}
	}
}

void Shader::EndConstantBuffer(int shaderType) const
{
	//ハッシュマップからキーのみを取り出し
	for (const auto& slot : constantBufferInfo_ | std::views::keys)
	{
		SetShaderConstantBuffer(-1, shaderType, slot);		//設定された定数バッファを解除する
	}
}
