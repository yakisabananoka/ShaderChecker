struct PixelOutput
{
    float4 color : SV_TARGET0;
    float4 colorR : SV_TARGET1;
    float4 colorG : SV_TARGET2;
    float4 colorB : SV_TARGET3;
};
#define PS_OUTPUT PixelOutput

#include "PixelShader2DHeader.hlsli"

//�}���`�����_�[�^�[�Q�b�g�̃T���v��

//�G���g���[�|�C���g
PS_OUTPUT main(PS_INPUT input)
{
    PS_OUTPUT output;
    output.color = tex.Sample(texSampler, input.uv); //�e�N�X�`������T���v�����O���s��

    //���l��0�̏ꍇ�͕`����s��Ȃ�(�{���̓��u�����h�ɂ�铧�߂��]�܂���)
    if (output.color.a == 0)
    {
        discard;
    }

    //RGB�̗v�f�𕪉�
    output.colorR = float4(output.color.r, 0, 0, output.color.a);
    output.colorG = float4(0, output.color.g, 0, output.color.a);
    output.colorB = float4(0, 0, output.color.b, output.color.a);

    return output; //���ʏo��
}
