#include "PixelShader2DHeader.hlsli"

//エントリーポイント
float4 main(PS_INPUT input) : SV_TARGET
{
    //テクスチャからサンプリングを行い出力
    return tex.Sample(texSampler, input.uv);
}
