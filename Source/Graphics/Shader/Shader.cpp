#include <ranges>
#include <DxLib.h>
#include "Shader.h"
#include "ConstantBuffer.h"

Shader::Shader(int handle):
	handle_(handle)
{
}

Shader::~Shader()
{
	DeleteShader(handle_);
}

void Shader::SetConstantBuffer(ConstantBufferBaseWeakPtr ptr, int slot)
{
	constantBufferInfos_[slot] = std::move(ptr);		//スロット番号をキーとしてハッシュマップに保持
}

Shader::Shader(Shader&& shader) noexcept :
	handle_(shader.handle_)
{
	shader.handle_ = -1;
}

Shader& Shader::operator=(Shader&& shader) noexcept
{
	handle_ = shader.handle_;
	shader.handle_ = -1;
	return *this;
}

void Shader::BeginConstantBuffer(int shaderType) const
{
	//設定された全定数バッファの取り出し
	for (const auto& [slot, ptr] : constantBufferInfos_)
	{
		//定数バッファが生きている場合はロック
		if (const auto constantBufferPtr = ptr.lock())
		{
			SetShaderConstantBuffer(constantBufferPtr->GetHandle(), shaderType, slot);		//シェーダーに対して定数バッファのハンドルをセット
		}
	}
}

void Shader::EndConstantBuffer(int shaderType) const
{
	//ハッシュマップからキーのみを取り出し
	for (const auto& slot : constantBufferInfos_ | std::views::keys)
	{
		SetShaderConstantBuffer(-1, shaderType, slot);							//設定された定数バッファを解除する
	}
}
