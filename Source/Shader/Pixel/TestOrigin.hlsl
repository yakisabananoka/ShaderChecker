#include "PixelShaderHeader.hlsli"

float4 main(PS_INPUT input) : SV_TARGET
{

    float4 result = tex.Sample(texSampler, input.uv);

    result.r = (sin(time) + 1) / 2;

    if(result.a==0)
    {
        discard;
    }

    return result;
}