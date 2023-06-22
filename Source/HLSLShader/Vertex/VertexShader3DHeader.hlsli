//�C���N���[�h�K�[�h
#if !defined(VERTEX_SHADER_3D_HEADER)
#define VERTEX_SHADER_3D_HEADER

//VERTEX_INPUT����`����Ă��Ȃ��ꍇ��MV1_VERTEX
#if !defined(VERTEX_INPUT)
#include "VertexInputTypeHeader.hlsli"
#define VERTEX_INPUT (DX_MV1_VERTEX_TYPE_1FRAME)
#endif

#include "VertexInputHeader.hlsli"
#include "../Common/CommonShader3DHeader.hlsli"
#include "../Common/VertexToPixelHeader.hlsli"

//���_�V�F�[�_�[�̓��͌^�̃f�t�H���g��`
#if !defined(VS_INPUT)
#define VS_INPUT VertexInput
#endif

//���_�V�F�[�_�[�̏o�͌^�̃f�t�H���g��`
#if !defined(VS_OUTPUT)
#define VS_OUTPUT VertexToPixel
#endif

#define DX_D3D11_COMMON_CONST_LIGHT_NUM			(6)			// ���ʃp�����[�^�̃��C�g�̍ő吔
#define DX_D3D11_VS_CONST_TEXTURE_MATRIX_NUM	(3)			// �e�N�X�`�����W�ϊ��s��̓]�u�s��̐�
#define DX_D3D11_VS_CONST_WORLD_MAT_NUM			(54)		// �g���C�A���O�����X�g��œ����Ɏg�p���郍�[�J�������[���h�s��̍ő吔

// �萔�o�b�t�@���_�V�F�[�_�[��{�p�����[�^
struct VsBase
{
    matrix antiViewportMatrix;  // �A���`�r���[�|�[�g�s��
    matrix projectionMatrix;    // �r���[�@���@�v���W�F�N�V�����s��
    float4x3 viewMatrix;        // ���[���h�@���@�r���[�s��
    float4x3 localWorldMatrix;  // ���[�J���@���@���[���h�s��

    float4 toonOutLineSize;     // �g�D�[���̗֊s���̑傫��
    float diffuseSource;        // �f�B�t���[�Y�J���[( 0.0f:�}�e���A��  1.0f:���_ )
    float specularSource;       // �X�y�L�����J���[(   0.0f:�}�e���A��  1.0f:���_ )
    float mulSpecularColor;     // �X�y�L�����J���[�l�ɏ�Z����l( �X�y�L�������������Ŏg�p )
    float padding;
};

// ���̑��̍s��
struct VsOtherMatrix
{
    float4 shadowMapLightViewProjectionMatrix[3][4];                // �V���h�E�}�b�v�p�̃��C�g�r���[�s��ƃ��C�g�ˉe�s�����Z��������
    float4 textureMatrix[DX_D3D11_VS_CONST_TEXTURE_MATRIX_NUM][2];  // �e�N�X�`�����W����p�s��
};

// �X�L�j���O���b�V���p�́@���[�J���@���@���[���h�s��
struct VsLocalWorldMatrix
{
    float4 lwMatrix[DX_D3D11_VS_CONST_WORLD_MAT_NUM * 3];           // ���[�J���@���@���[���h�s��
};

// ���_�V�F�[�_�[�E�s�N�Z���V�F�[�_�[���ʃp�����[�^
cbuffer cbD3D11_CONST_BUFFER_COMMON : register(b0)
{
    Common common;
};

// ��{�p�����[�^
cbuffer cbD3D11_CONST_BUFFER_VS_BASE : register(b1)
{
    VsBase base;
};

// ���̑��̍s��
cbuffer cbD3D11_CONST_BUFFER_VS_OTHERMATRIX : register(b2)
{
    VsOtherMatrix otherMatrix;
};

// �X�L�j���O���b�V���p�́@���[�J���@���@���[���h�s��
cbuffer cbD3D11_CONST_BUFFER_VS_LOCALWORLDMATRIX : register(b3)
{
    VsLocalWorldMatrix localWorldMatrix;
};

#endif