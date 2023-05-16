#include "PixelShader2DHeader.hlsli"

cbuffer Test : register(b3)
{
    float time;                 //�o�ߎ���
}

//�G���g���[�|�C���g
float4 main(PS_INPUT input) : SV_TARGET
{
    float4 result = tex.Sample(texSampler, input.uv); //�e�N�X�`������T���v�����O���s��

    result.r = (sin(time) + 1) / 2; //�萔�o�b�t�@�ɓ����Ă����o�ߎ��Ԃ��g�p����R�v�f��sin�g�ŕϓ�������

    //���l��0�̏ꍇ�͕`����s��Ȃ�(�{���̓��u�����h�ɂ�铧�߂��]�܂���)
    if (result.a == 0)
    {
        discard;
    }

    return result; //���ʏo��
}
