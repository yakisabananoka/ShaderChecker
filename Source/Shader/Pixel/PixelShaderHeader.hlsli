
struct PS_INPUT
{
    float4 diffuse : COLOR0;        //拡散反射の色
    float4 specular : COLOR1;       //鏡面反射の色
    float2 uv : TEXCOORD0;          //UV値
    float2 suv : TEXCOORD1;         //サブテクスチャのUV値
};

cbuffer Test : register(b0)
{
    float time;     //経過時間
}

Texture2D tex : register(t0);               //テクスチャ
SamplerState texSampler : register(s0);     //サンプラー
