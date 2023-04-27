#include <ranges>
#include <DxLib.h>
#include "Shader.h"
#include "ConstantBuffer.h"

void Shader::SetConstantBuffer(ConstantBufferBaseWeakPtr ptr, int slot)
{
	constantBufferInfos_[slot] = std::move(ptr);		//スロット番号をキーとしてハッシュマップに保持
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
