struct PixelOutput
{
    float4 color : SV_TARGET0;
    float4 colorR : SV_TARGET1;
    float4 colorG : SV_TARGET2;
    float4 colorB : SV_TARGET3;
};
#define PS_OUTPUT PixelOutput

#include "PixelShader2DHeader.hlsli"

//マルチレンダーターゲットのサンプル

//エントリーポイント
PS_OUTPUT main(PS_INPUT input)
{
    PS_OUTPUT output;
    output.color = tex.Sample(texSampler, input.uv); //テクスチャからサンプリングを行う

    //α値が0の場合は描画を行わない(本来はαブレンドによる透過が望ましい)
    if (output.color.a == 0)
    {
        discard;
    }

    //RGBの要素を分解
    output.colorR = float4(output.color.r, 0, 0, output.color.a);
    output.colorG = float4(0, output.color.g, 0, output.color.a);
    output.colorB = float4(0, 0, output.color.b, output.color.a);

    return output; //結果出力
}
