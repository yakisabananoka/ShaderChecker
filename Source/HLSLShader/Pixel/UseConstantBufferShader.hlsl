#include "PixelShader2DHeader.hlsli"

cbuffer Test : register(b3)
{
    float time;         //�o�ߎ���
    float padding[3];   //�p�f�B���O
}

//�G���g���[�|�C���g
PS_OUTPUT main(PS_INPUT input) : SV_TARGET
{
    //�e�N�X�`������T���v�����O���s��
    float4 result = tex.Sample(texSampler, input.uv);

    //�萔�o�b�t�@�ɓ����Ă����o�ߎ��Ԃ��g�p����R�v�f��sin�g�ŕϓ�������
    result.r = (sin(time) + 1) / 2;

    //���l��0�̏ꍇ�͕`����s��Ȃ�(�{���̓��u�����h�ɂ�铧�߂��]�܂���)
    if (result.a == 0)
    {
        discard;
    }

    return result; //���ʏo��
}
