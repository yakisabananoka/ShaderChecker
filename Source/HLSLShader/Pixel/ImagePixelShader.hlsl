#include "PixelShader2DHeader.hlsli"

//�G���g���[�|�C���g
float4 main(PS_INPUT input) : SV_TARGET
{
    //�e�N�X�`������T���v�����O���s���o��
    return tex.Sample(texSampler, input.uv);
}
