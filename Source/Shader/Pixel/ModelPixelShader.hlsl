#include "PixelShader3DHeader.hlsli"

PS_OUTPUT main(PS_INPUT input) : SV_TARGET
{
	return PS_OUTPUT(input.uv, 1.0f, 1.0f);
}
