
struct PS_INPUT
{
    float4 diffuse : COLOR0;        //�g�U���˂̐F
    float4 specular : COLOR1;       //���ʔ��˂̐F
    float2 uv : TEXCOORD0;          //UV�l
    float2 suv : TEXCOORD1;         //�T�u�e�N�X�`����UV�l
};

cbuffer Test : register(b0)
{
    float time;     //�o�ߎ���
}

Texture2D tex : register(t0);               //�e�N�X�`��
SamplerState texSampler : register(s0);     //�T���v���[
