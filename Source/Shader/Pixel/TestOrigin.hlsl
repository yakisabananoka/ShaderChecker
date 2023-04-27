﻿#include "PixelShaderHeader.hlsli"      //ピクセルシェーダー用のヘッダをインクルード

//エントリーポイント
float4 main(PS_INPUT input) : SV_TARGET
{
    float4 result = tex.Sample(texSampler, input.uv);       //テクスチャからサンプリングを行う

    result.r = (sin(time) + 1) / 2;     //定数バッファに入ってきた経過時間を使用してR要素をsin波で変動させる

    //α値が0の場合は描画を行わない(本来はαブレンドによる透過が望ましい)
    if(result.a == 0)
    {
        discard;
    }

    return result;      //結果出力
}