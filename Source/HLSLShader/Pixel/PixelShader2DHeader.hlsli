//�C���N���[�h�K�[�h
#if !defined(PIXEL_SHADER_2D_HEADER)
	#define PIXEL_SHADER_2D_HEADER

	//�s�N�Z���V�F�[�_�[�̓��͌^�̃f�t�H���g��`
	#if !defined(PS_INPUT)
		struct PixelInput
		{
		    float4 svPos : SV_POSITION;
		    float4 diffuse : COLOR0;		//�g�U���˂̐F
		    //float4 specular : COLOR1;		//���ʔ��˂̐F(����ver3.24c�ȍ~�̃��C�u�������g�p���Ă���ꍇ�̓R�����g���O��)
		    float2 uv : TEXCOORD0;			//UV�l
		    float2 suv : TEXCOORD1;			//�T�u�e�N�X�`����UV�l
		};
		#define PS_INPUT PixelInput

	#endif

	//�s�N�Z���V�F�[�_�[�̏o�͌^�̃f�t�H���g��`
	#if !defined(PS_OUTPUT)
		struct PixelOutput
		{
		    float color : SV_TARGET;
		};
		#define PS_OUTPUT PixelOutput
	#endif

	Texture2D tex : register(t0);               //�e�N�X�`��
	SamplerState texSampler : register(s0);     //�T���v���[

#endif
