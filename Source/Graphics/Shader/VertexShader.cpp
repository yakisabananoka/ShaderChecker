﻿#include <DxLib.h>
#include "VertexShader.h"

VertexShaderPtr VertexShader::Create(const std::filesystem::path& path)
{
	return VertexShaderPtr(new VertexShader(path));
}

void VertexShader::Begin(void) const
{
	SetUseVertexShader(handle_);							//頂点シェーダーの使用を設定
	BeginConstantBuffer(DX_SHADERTYPE_VERTEX);				//定数バッファの開始処理
}

void VertexShader::End(void) const
{
	EndConstantBuffer(DX_SHADERTYPE_VERTEX);				//定数バッファの終了処理
	SetUseVertexShader(-1);									//頂点シェーダーの使用を解除
}

VertexShader::VertexShader(const std::filesystem::path& path) :
	Shader(LoadVertexShader(path.string().c_str()))
{
}
