//�C���N���[�h�K�[�h
#if !defined(VERTEX_TO_PIXEL_HEADER)
	#define VERTEX_TO_PIXEL_HEADER

	#if !defined(VERTEX_TO_PIXEL_TYPE)
		#include "VertexToPixelTypeHeader.hlsli"
		#define VERTEX_TO_PIXEL_TYPE VERTEX_TO_PIXEL_TYPE_DEFAULT
	#endif

	#if (VERTEX_TO_PIXEL_TYPE == VERTEX_TO_PIXEL_TYPE_DEFAULT)
		//�@���}�b�v�Ȃ��̏ꍇ
		struct VertexToPixel
		{
		    float4 svPos : SV_POSITION;		//�ʒu(�v���W�F�N�V����)
		    float3 worldPos : POSITION0;	//�ʒu(���[���h)
		    float3 viewPos : POSITION1;		//�ʒu(�r���[)
		    float3 viewNorm : NORMAL0;		//�@��
		    float4 diffuse : COLOR0;		//�g�U���ːF
		    float4 specular : COLOR1;		//���ʔ��ːF
		    float2 uv : TEXCOORD;			//UV�l
		};
	#elif (VERTEX_TO_PIXEL_TYPE == VERTEX_TO_PIXEL_TYPE_NORMAL_MAP)
		//�@���}�b�v����̏ꍇ
		struct VertexToPixel
		{
			float4 svPos : SV_POSITION;		//�ʒu(�v���W�F�N�V����)
		    float3 worldPos : POSITION0;	//�ʒu(���[���h)
		    float3 viewPos : POSITION1;		//�ʒu(�r���[)
		    float3 viewTan : TANGENT0;		//�ڐ�
		    float3 viewBin : BINORMAL;		//�]�@��
		    float3 viewNorm : NORMAL0;		//�@��
		    float4 diffuse : COLOR0;		//�g�U���ːF
		    float4 specular : COLOR1;		//���ʔ��ːF
		    float2 uv : TEXCOORD;			//UV�l
		};
	#endif
#endif

