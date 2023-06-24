#include "VertexShader3DHeader.hlsli"

//�G���g���[�|�C���g
VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT ret;
    ret.svPos = float4(input.pos, 1.0f);

    //���[�J�����W�n�����[���h���W�n
    ret.worldPos = mul(ret.svPos, base.localWorldMatrix);
    ret.svPos.xyz = ret.worldPos;

    //���[���h���W�n���r���[���W�n
    ret.viewPos = mul(ret.svPos, base.viewMatrix);
    ret.svPos.xyz = ret.viewPos;

    //�r���[���W�n���v���W�F�N�V�������W�n
    ret.svPos = mul(ret.svPos, base.projectionMatrix);

    //�@��(�r���[)���v�Z
    ret.viewNorm = normalize(mul(float4(input.norm, 0.0f), base.localWorldMatrix));
    ret.viewNorm = normalize(mul(float4(ret.viewNorm, 0.0f), base.viewMatrix));

    ret.uv = input.uv0.xy;              //UV����
    ret.diffuse = input.diffuse;        //�g�U���ːF����
    ret.specular = input.specular;      //���ʔ��ːF����

	return ret;
}