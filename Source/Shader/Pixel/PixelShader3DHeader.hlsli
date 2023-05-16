#include "../Common/CommonShader3DHeader.hlsli"
#include "../Common/VertexToPixelHeader.hlsli"

#if !defined(PS_INPUT)
#define PS_INPUT VertexToPixel
#endif

#if !defined(PS_OUTPUT)
#define PS_OUTPUT float4
#endif

#define DX_D3D11_PS_CONST_FILTER_SIZE	(1280)	    // �t�B���^�[�p�萔�o�b�t�@�̃T�C�Y

// �V���h�E�}�b�v�p�����[�^
struct ShadowMap
{
    float adjustDepth;      // 臒l�[�x�␳�l
    float gradationParam;   // �O���f�[�V�����͈�
    float enable_Light0;    // ���C�g�O�ւ̓K�p���
    float enable_Light1;    // ���C�g�P�ւ̓K�p���

    float enable_Light2;    // ���C�g�Q�ւ̓K�p���
    float3 padding;         // �p�f�B���O
};

// �萔�o�b�t�@�s�N�Z���V�F�[�_�[��{�p�����[�^
struct PsBase
{
    float4 factorColor;             // �A���t�@�l��

    float mulAlphaColor;            // �J���[�ɃA���t�@�l����Z���邩�ǂ���( 0.0f:��Z���Ȃ�  1.0f:��Z���� )
    float alphaTestRef;             // �A���t�@�e�X�g�Ŏg�p�����r�l
    float2 padding1;

    int alphaTestCmpMode;           // �A���t�@�e�X�g��r���[�h( DX_CMP_NEVER �Ȃ� )
    int noLightAngleAttenuation;    // ���C�g�̊p�x�������s��Ȃ���( 0:�������s��   1:�������s��Ȃ� )
    int2 padding2;

    float4 ignoreTextureColor;      // �e�N�X�`���J���[���������p�J���[

    float4 drawAddColor;            // ���Z����F
};

// �萔�o�b�t�@�V���h�E�}�b�v�p�����[�^
struct PsShadowMap
{
    ShadowMap data[3];
};

// ���_�V�F�[�_�[�E�s�N�Z���V�F�[�_�[���ʃp�����[�^
cbuffer cbD3D11_CONST_BUFFER_COMMON : register(b0)
{
    Common common;
};
// ��{�p�����[�^
cbuffer cbD3D11_CONST_BUFFER_PS_BASE : register(b1)
{
    PsBase base;
};
// �V���h�E�}�b�v�p�����[�^
cbuffer cbD3D11_CONST_BUFFER_PS_SHADOWMAP : register(b2)
{
    PsShadowMap shadowMap;
};