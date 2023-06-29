#include "PixelShader3DHeader.hlsli"

//�G���g���[�|�C���g
PS_OUTPUT main(PS_INPUT input) : SV_TARGET
{
    //HSV�Ŋ�F��ݒ�
    float4 result = float4(0.3f, 0.15f, 1.f, 1.0f);

    //�F����@���Ǝ����̌X���̍������g���ĕϓ�������
    result.r += dot(-normalize(input.viewPos), normalize(input.viewNorm));

    //�F����0�`1�̊Ԃŏz������
    result.r = fmod(result.r, 1.f);

    //HSV����RGB�ɕϊ�
    result.rgb = HSVtoRGB(result.rgb);

    //0�`1�̊ԂɊۂ߂�
    return saturate(result);
}
