//�C���N���[�h�K�[�h
#if !defined(PIXEL_SHADER_3D_HEADER)
	#define PIXEL_SHADER_3D_HEADER

	#include "../Common/CommonShader3DHeader.hlsli"

	//�s�N�Z���V�F�[�_�[�̓��͌^�̃f�t�H���g��`
	#if !defined(PS_INPUT)
		#include "../Common/VertexToPixelHeader.hlsli"
		#define PS_INPUT VertexToPixel
	#endif

	//�s�N�Z���V�F�[�_�[�̏o�͌^�̃f�t�H���g��`
	#if !defined(PS_OUTPUT)
		#define PS_OUTPUT float4
	#endif

	#include "PixelStructuresHeader.hlsli"

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

	#if defined(BUMPMAP)
		SamplerState normalMapSampler             : register(s1);    		// �@���}�b�v�e�N�X�`��
		Texture2D    normalMapTexture             : register(t1);	    	// �@���}�b�v�e�N�X�`��
	#endif // BUMPMAP

	#if defined(USE_SPETEX)
		SamplerState specularMapSampler           : register(s2);    		// �X�y�L�����}�b�v�e�N�X�`��
		Texture2D    specularMapTexture           : register(t2);	    	// �X�y�L�����}�b�v�e�N�X�`��
	#endif // USE_SPETEX

	#if defined(TOON)
		SamplerState toonDiffuseGradSampler       : register(s3);   		// �g�D�[�������_�����O�p�f�B�t���[�Y�J���[�O���f�[�V�����e�N�X�`��
		Texture2D    toonDiffuseGradTexture       : register(t3); 	    	// �g�D�[�������_�����O�p�f�B�t���[�Y�J���[�O���f�[�V�����e�N�X�`��

		SamplerState toonSpecularGradSampler      : register(s4);	    	// �g�D�[�������_�����O�p�X�y�L�����J���[�O���f�[�V�����e�N�X�`��
		Texture2D    toonSpecularGradTexture      : register(t4);   		// �g�D�[�������_�����O�p�X�y�L�����J���[�O���f�[�V�����e�N�X�`��

		#if defined(TOON_SPHEREOP_MUL) || defined(TOON_SPHEREOP_ADD)
			SamplerState toonSphereMapSampler         : register(s5);     		// �g�D�[�������_�����O�p�X�t�B�A�}�b�v�e�N�X�`��
			Texture2D    toonSphereMapTexture         : register(t5);	    	// �g�D�[�������_�����O�p�X�t�B�A�}�b�v�e�N�X�`��
		#endif // TOON_SPHEREOP_MUL || TOON_SPHEREOP_ADD

		SamplerState toonRGBtoVMaxRGBVolumeSampler: register(s6);	    	// �g�D�[�������_�����O�pRGB�P�x�O�a�����p�{�����[���e�N�X�`��
		Texture3D    toonRGBtoVMaxRGBVolumeTexture: register(t6);		    // �g�D�[�������_�����O�pRGB�P�x�O�a�����p�{�����[���e�N�X�`��
	#endif // TOON

	#if defined(SUBTEXTUREMODE)
		SamplerState subSampler                   : register(s7);           // �T�u�e�N�X�`��
		Texture2D subTexture                      : register(t7);           // �T�u�e�N�X�`��
	#endif // SUBTEXTUREMODE != 0

	#if defined(SHADOWMAP)
		SamplerState shadowMap0Sampler            : register(s8);	    	// �V���h�E�}�b�v�O�e�N�X�`��
		Texture2D    shadowMap0Texture            : register(t8);		    // �V���h�E�}�b�v�O�e�N�X�`��

		SamplerState shadowMap1Sampler            : register(s9);   		// �V���h�E�}�b�v�P�e�N�X�`��
		Texture2D    shadowMap1Texture            : register(t9);	    	// �V���h�E�}�b�v�P�e�N�X�`��

		SamplerState shadowMap2Sampler            : register(s10); 	    	// �V���h�E�}�b�v�Q�e�N�X�`��
		Texture2D    shadowMap2Texture            : register(t10);	    	// �V���h�E�}�b�v�Q�e�N�X�`��
	#endif

	#include "PixelFunctionHeader.hlsli"

#endif
