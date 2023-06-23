//�C���N���[�h�K�[�h
#if !defined(VERTEX_SHADER_3D_HEADER)
	#define VERTEX_SHADER_3D_HEADER

	#include "../Common/CommonShader3DHeader.hlsli"

	//���_�V�F�[�_�[�̓��͌^�̃f�t�H���g��`
	#if !defined(VS_INPUT)
		#include "VertexInputHeader.hlsli"
		#define VS_INPUT VertexInput
	#endif

	//���_�V�F�[�_�[�̏o�͌^�̃f�t�H���g��`
	#if !defined(VS_OUTPUT)
		#include "../Common/VertexToPixelHeader.hlsli"
		#define VS_OUTPUT VertexToPixel
	#endif

	#include "VertexStructuresHeader.hlsli"
	#include "VertexFunctionHeader.hlsli"

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