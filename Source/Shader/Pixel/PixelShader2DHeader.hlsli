struct PS_INPUT
{
    float4 svPos : SV_POSITION;
    float4 diffuse : COLOR0;    //�g�U���˂̐F
    float2 uv : TEXCOORD0;      //UV�l
    float2 suv : TEXCOORD1;     //�T�u�e�N�X�`����UV�l
};

Texture2D tex : register(t0);               //�e�N�X�`��
SamplerState texSampler : register(s0);     //�T���v���[
