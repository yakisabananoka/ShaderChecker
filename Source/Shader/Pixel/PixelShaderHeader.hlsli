
struct PS_INPUT
{
    float4 diffuse : COLOR0;
    float4 specular : COLOR1;
    float2 uv : TEXCOORD0;
    float2 suv : TEXCOORD1;
};

cbuffer Test : register(b0)
{
    float time;
}

Texture2D tex : register(t0);
SamplerState texSampler : register(s0);
