//�C���N���[�h�K�[�h
#if !defined(VERTEX_INPUT_HEADER)
	#define VERTEX_INPUT_HEADER

	#include "VertexInputTypeHeader.hlsli"

	//VERTEX_INPUT_TYPE����`����Ă��Ȃ��ꍇ��DX_MV1_VERTEX_TYPE_1FRAME�ɐݒ�
	#if !defined(VERTEX_INPUT_TYPE)
		#define VERTEX_INPUT_TYPE DX_MV1_VERTEX_TYPE_1FRAME
	#endif

	#if (VERTEX_INPUT_TYPE == DX_MV1_VERTEX_TYPE_1FRAME)
		//1�t���[���̉e�����󂯂钸�_
		struct VertexInput
		{
		    float3 pos : POSITION;          // ���W(���[�J�����)
		    float3 norm : NORMAL;           // �@��(���[�J�����)
		    float4 diffuse : COLOR0;        // �f�B�t���[�Y�J���[
		    float4 specular : COLOR1;       // �X�y�L�����J���[
		    float4 uv0 : TEXCOORD0;         // �e�N�X�`�����W
		    float4 uv1 : TEXCOORD1;         // �T�u�e�N�X�`�����W
		};
	#elif (VERTEX_INPUT_TYPE == DX_MV1_VERTEX_TYPE_4FRAME)
		//1�`4�t���[���̉e�����󂯂钸�_
		struct VertexInput
		{
		    float3 pos : POSITION;              // ���W(���[�J�����)
		    float3 norm : NORMAL;               // �@��(���[�J�����)
		    float4 diffuse : COLOR0;            // �f�B�t���[�Y�J���[
		    float4 specular : COLOR1;           // �X�y�L�����J���[
		    float4 uv0 : TEXCOORD0;             // �e�N�X�`�����W
		    float4 uv1 : TEXCOORD1;             // �T�u�e�N�X�`�����W
		    int4 blendIndices0 : BLENDINDICES0; // �{�[�������p Float�^�萔�z��C���f�b�N�X0
		    float4 blendWeight0 : BLENDWEIGHT0; // �{�[�������p�E�G�C�g�l0
		};
	#elif (VERTEX_INPUT_TYPE == DX_MV1_VERTEX_TYPE_8FRAME)
		//5�`8�t���[���̉e�����󂯂钸�_
		struct VertexInput
		{
		    float3 pos : POSITION;              // ���W(���[�J�����)
		    float3 norm : NORMAL;               // �@��(���[�J�����)
		    float4 diffuse : COLOR0;            // �f�B�t���[�Y�J���[
		    float4 specular : COLOR1;           // �X�y�L�����J���[
		    float4 uv0 : TEXCOORD0;             // �e�N�X�`�����W
		    float4 uv1 : TEXCOORD1;             // �T�u�e�N�X�`�����W
		    int4 blendIndices0 : BLENDINDICES0; // �{�[�������p Float�^�萔�z��C���f�b�N�X0
		    float4 blendWeight0 : BLENDWEIGHT0; // �{�[�������p�E�G�C�g�l0
		    int4 blendIndices1 : BLENDINDICES1; // �{�[�������p Float�^�萔�z��C���f�b�N�X1
		    float4 blendWeight1 : BLENDWEIGHT1; // �{�[�������p�E�G�C�g�l1
		};
	#elif (VERTEX_INPUT_TYPE == DX_MV1_VERTEX_TYPE_NMAP_1FRAME)
		//�@���}�b�v�̏�񂪊܂܂��1�t���[���̉e�����󂯂钸�_
		struct VertexInput
		{
		    float3 pos : POSITION;              // ���W(���[�J�����)
		    float3 norm : NORMAL;               // �@��(���[�J�����)
		    float4 diffuse : COLOR0;            // �f�B�t���[�Y�J���[
		    float4 specular : COLOR1;           // �X�y�L�����J���[
		    float4 uv0 : TEXCOORD0;             // �e�N�X�`�����W
		    float4 uv1 : TEXCOORD1;             // �T�u�e�N�X�`�����W
		    float3 tan : TANGENT0;              // �ڐ�(���[�J�����)
		    float3 bin : BINORMAL0;             // �]�@��(���[�J�����)
		};
	#elif (VERTEX_INPUT_TYPE == DX_MV1_VERTEX_TYPE_NMAP_4FRAME)
		//�@���}�b�v�̏�񂪊܂܂��1�`4�t���[���̉e�����󂯂钸�_
		struct VertexInput
		{
		    float3 pos : POSITION;              // ���W(���[�J�����)
		    float3 norm : NORMAL;               // �@��(���[�J�����)
		    float4 diffuse : COLOR0;            // �f�B�t���[�Y�J���[
		    float4 specular : COLOR1;           // �X�y�L�����J���[
		    float4 uv0 : TEXCOORD0;             // �e�N�X�`�����W
		    float4 uv1 : TEXCOORD1;             // �T�u�e�N�X�`�����W
		    float3 tan : TANGENT0;              // �ڐ�(���[�J�����)
		    float3 bin : BINORMAL0;             // �]�@��(���[�J�����)
		    int4 blendIndices0 : BLENDINDICES0; // �{�[�������p Float�^�萔�z��C���f�b�N�X0
		    float4 blendWeight0 : BLENDWEIGHT0; // �{�[�������p�E�G�C�g�l0
		};
	#elif (VERTEX_INPUT_TYPE == DX_MV1_VERTEX_TYPE_NMAP_8FRAME)
		//�@���}�b�v�̏�񂪊܂܂��5�`8�t���[���̉e�����󂯂钸�_
		struct VertexInput
		{
		    float3 pos : POSITION;              // ���W(���[�J�����)
		    float3 norm : NORMAL;               // �@��(���[�J�����)
		    float4 diffuse : COLOR0;            // �f�B�t���[�Y�J���[
		    float4 specular : COLOR1;           // �X�y�L�����J���[
		    float4 uv0 : TEXCOORD0;             // �e�N�X�`�����W
		    float4 uv1 : TEXCOORD1;             // �T�u�e�N�X�`�����W
		    float3 tan : TANGENT0;              // �ڐ�(���[�J�����)
		    float3 bin : BINORMAL0;             // �]�@��(���[�J�����)
		    int4 blendIndices0 : BLENDINDICES0; // �{�[�������p Float�^�萔�z��C���f�b�N�X0
		    float4 blendWeight0 : BLENDWEIGHT0; // �{�[�������p�E�G�C�g�l0
		    int4 blendIndices1 : BLENDINDICES1; // �{�[�������p Float�^�萔�z��C���f�b�N�X1
		    float4 blendWeight1 : BLENDWEIGHT1; // �{�[�������p�E�G�C�g�l1
		};
	#elif (VERTEX_INPUT_TYPE == DX_VERTEX_TYPE_ORIGIN)
		//DrawPolygon3D���̊֐����g�p�����ꍇ�ɑ����钸�_
		struct VertexInput
		{
			float3 pos : POSITION0;     //���W(���[�J�����)
		    float4 subPos : POSITION1;  //�⏕���W
		    float3 norm : NORMAL;       //�@��
		    float3 tan : TANGENT;       //�ڐ�
		    float3 bin : BINORMAL;      //�]�@��
		    float4 diffuse : COLOR0;    //�f�B�t���[�Y�J���[
		    float4 specular : COLOR1;   //�X�y�L�����J���[
		    float2 uv0 : TEXCOORD0;     //�e�N�X�`�����W0
		    float2 uv1 : TEXCOORD1;     //�e�N�X�`�����W1
		};
	#endif

#endif
