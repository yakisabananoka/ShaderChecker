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

SamplerState diffuseMapSampler            : register(s0);           // �f�B�t���[�Y�}�b�v�e�N�X�`��
Texture2D diffuseMapTexture               : register(t0);           // �f�B�t���[�Y�}�b�v�e�N�X�`��

#if BUMPMAP
SamplerState normalMapSampler             : register(s1);    		// �@���}�b�v�e�N�X�`��
Texture2D    normalMapTexture             : register(t1);	    	// �@���}�b�v�e�N�X�`��
#endif // BUMPMAP

#if USE_SPETEX
SamplerState specularMapSampler           : register(s2);    		// �X�y�L�����}�b�v�e�N�X�`��
Texture2D    specularMapTexture           : register(t2);	    	// �X�y�L�����}�b�v�e�N�X�`��
#endif // USE_SPETEX

#if TOON
SamplerState toonDiffuseGradSampler       : register(s3);   		// �g�D�[�������_�����O�p�f�B�t���[�Y�J���[�O���f�[�V�����e�N�X�`��
Texture2D    toonDiffuseGradTexture       : register(t3); 	    	// �g�D�[�������_�����O�p�f�B�t���[�Y�J���[�O���f�[�V�����e�N�X�`��

SamplerState toonSpecularGradSampler      : register(s4);	    	// �g�D�[�������_�����O�p�X�y�L�����J���[�O���f�[�V�����e�N�X�`��
Texture2D    toonSpecularGradTexture      : register(t4);   		// �g�D�[�������_�����O�p�X�y�L�����J���[�O���f�[�V�����e�N�X�`��

#if TOON_SPHEREOP_MUL || TOON_SPHEREOP_ADD
SamplerState toonSphereMapSampler         : register(s5);     		// �g�D�[�������_�����O�p�X�t�B�A�}�b�v�e�N�X�`��
Texture2D    toonSphereMapTexture         : register(t5);	    	// �g�D�[�������_�����O�p�X�t�B�A�}�b�v�e�N�X�`��
#endif // TOON_SPHEREOP_MUL || TOON_SPHEREOP_ADD

SamplerState toonRGBtoVMaxRGBVolumeSampler: register(s6);	    	// �g�D�[�������_�����O�pRGB�P�x�O�a�����p�{�����[���e�N�X�`��
Texture3D    toonRGBtoVMaxRGBVolumeTexture: register(t6);		    // �g�D�[�������_�����O�pRGB�P�x�O�a�����p�{�����[���e�N�X�`��
#endif // TOON

#if SUBTEXTUREMODE
SamplerState subSampler                   : register(s7);           // �T�u�e�N�X�`��
Texture2D subTexture                      : register(t7);           // �T�u�e�N�X�`��
#endif // SUBTEXTUREMODE != 0

#if SHADOWMAP
SamplerState shadowMap0Sampler            : register(s8);	    	// �V���h�E�}�b�v�O�e�N�X�`��
Texture2D    shadowMap0Texture            : register(t8);		    // �V���h�E�}�b�v�O�e�N�X�`��

SamplerState shadowMap1Sampler            : register(s9);   		// �V���h�E�}�b�v�P�e�N�X�`��
Texture2D    shadowMap1Texture            : register(t9);	    	// �V���h�E�}�b�v�P�e�N�X�`��

SamplerState shadowMap2Sampler            : register(s10); 	    	// �V���h�E�}�b�v�Q�e�N�X�`��
Texture2D    shadowMap2Texture            : register(t10);	    	// �V���h�E�}�b�v�Q�e�N�X�`��
#endif
