#include <DxLib.h>
#include "PixelShader.h"

PixelShader::PixelShader(std::filesystem::path path)
{
	handle_ = LoadPixelShader(path.string().c_str());
}

PixelShader::~PixelShader()
{
	DeleteShader(handle_);
}

void PixelShader::Begin(void) const
{
	SetUsePixelShader(handle_);
	BeginConstantBuffer(DX_SHADERTYPE_PIXEL);
}

void PixelShader::End(void) const
{
	EndConstantBuffer(DX_SHADERTYPE_PIXEL);
	SetUsePixelShader(-1);
}
