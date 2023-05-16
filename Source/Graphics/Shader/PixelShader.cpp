﻿#include <DxLib.h>
#include "PixelShader.h"

PixelShader::PixelShader(std::filesystem::path path) :
	Shader(LoadPixelShader(path.string().c_str()))
{
}

void PixelShader::Begin(void) const
{
	SetUsePixelShader(handle_);								//ピクセルシェーダーの使用を設定
	BeginConstantBuffer(DX_SHADERTYPE_PIXEL);				//定数バッファの開始処理
}

void PixelShader::End(void) const
{
	EndConstantBuffer(DX_SHADERTYPE_PIXEL);					//定数バッファの終了処理
	SetUsePixelShader(-1);									//ピクセルシェーダーの使用を解除
}