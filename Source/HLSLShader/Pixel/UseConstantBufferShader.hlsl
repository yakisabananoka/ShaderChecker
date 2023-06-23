#include "PixelShader2DHeader.hlsli"

cbuffer Test : register(b3)
{
    float time;         //経過時間
    float padding[3];   //パディング
}

//エントリーポイント
PS_OUTPUT main(PS_INPUT input) : SV_TARGET
{
    //テクスチャからサンプリングを行う
    float4 result = tex.Sample(texSampler, input.uv);

    //定数バッファに入ってきた経過時間を使用してR要素をsin波で変動させる
    result.r = (sin(time) + 1) / 2;

    //α値が0の場合は描画を行わない(本来はαブレンドによる透過が望ましい)
    if (result.a == 0)
    {
        discard;
    }

    return result; //結果出力
}
