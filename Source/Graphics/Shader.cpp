#include <ranges>
#include <DxLib.h>
#include "Shader.h"
#include "ConstantBuffer.h"

void Shader::SetConstantBuffer(ConstantBufferBaseWeakPtr ptr, int slot)
{
	constantBufferInfos_[slot] = std::move(ptr);
}

void Shader::BeginConstantBuffer(int shaderType) const
{
	for (const auto& [slot, ptr] : constantBufferInfos_)
	{
		if (const auto constantBufferPtr = ptr.lock())
		{
			SetShaderConstantBuffer(constantBufferPtr->GetHandle(), shaderType, slot);
		}
	}
}

void Shader::EndConstantBuffer(int shaderType) const
{
	for (const auto& slot : constantBufferInfos_ | std::views::keys)
	{
		SetShaderConstantBuffer(-1, shaderType, slot);
	}
}
