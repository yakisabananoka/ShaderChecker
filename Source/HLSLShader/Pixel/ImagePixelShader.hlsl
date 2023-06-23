#include "PixelShader2DHeader.hlsli"

//エントリーポイント
PS_OUTPUT main(PS_INPUT input) : SV_TARGET
{
    //テクスチャからサンプリングを行い出力
    return tex.Sample(texSampler, input.uv);
}
