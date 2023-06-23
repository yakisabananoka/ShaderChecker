//�C���N���[�h�K�[�h
#if !defined(COMMON_STRUCTURES_HEADER)
	#define COMMON_STRUCTURES_HEADER

	#define DX_D3D11_COMMON_CONST_LIGHT_NUM (6)         // ���ʃp�����[�^�̃��C�g�̍ő吔

	#define DX_VERTEXLIGHTING_LIGHT_NUM		(3)		    // ���_�P�ʃ��C�e�B���O�œ����Ɏg�p�ł��郉�C�g�̍ő吔
	#define DX_PIXELLIGHTING_LIGHT_NUM		(6)		    // �s�N�Z���P�ʃ��C�e�B���O�œ����Ɏg�p�ł��郉�C�g�̍ő吔

	#define DX_LIGHTTYPE_POINT				(1)			// �|�C���g���C�g
	#define DX_LIGHTTYPE_SPOT				(2)			// �X�|�b�g���C�g
	#define DX_LIGHTTYPE_DIRECTIONAL		(3)			// �f�B���N�V���i�����C�g

	// �}�e���A���p�����[�^
	struct Material
	{
	    float4 diffuse;             // �f�B�t���[�Y�J���[
	    float4 specular;            // �X�y�L�����J���[
	    float4 ambientEmissive;     // �}�e���A���G�~�b�V�u�J���[ + �}�e���A���A���r�G���g�J���[ * �O���[�o���A���r�G���g�J���[
		
	    float power;                // �X�y�L�����̋���
	    float typeParam0;           // �}�e���A���^�C�v�p�����[�^0
	    float typeParam1;           // �}�e���A���^�C�v�p�����[�^1
	    float typeParam2;           // �}�e���A���^�C�v�p�����[�^2
	};

	// �t�H�O�p�����[�^
	struct VsFog
	{
	    float linearAdd;            // �t�H�O�p�p�����[�^ end / ( end - start )
	    float linearDiv;            // �t�H�O�p�p�����[�^ -1  / ( end - start )
	    float density;              // �t�H�O�p�p�����[�^ density
	    float e;                    // �t�H�O�p�p�����[�^ ���R�ΐ��̒�

	    float4 color;               // �J���[
	};

	// ���C�g�p�����[�^
	struct Light
	{
	    int type;               // ���C�g�^�C�v( DX_LIGHTTYPE_POINT �Ȃ� )
	    int3 padding1;          // �p�f�B���O�P
		
	    float3 position;        // ���W( �r���[��� )
	    float rangePow2;        // �L�������̂Q��
		
	    float3 direction;       // ����( �r���[��� )
	    float fallOff;          // �X�|�b�g���C�g�pFallOff
		
	    float3 diffuse;         // �f�B�t���[�Y�J���[
	    float spotParam0;       // �X�|�b�g���C�g�p�p�����[�^�O( cos( Phi / 2.0f ) )
		
	    float3 specular;        // �X�y�L�����J���[
	    float spotParam1;       // �X�|�b�g���C�g�p�p�����[�^�P( 1.0f / ( cos( Theta / 2.0f ) - cos( Phi / 2.0f ) ) )
		
	    float4 ambient;         // �A���r�G���g�J���[�ƃ}�e���A���̃A���r�G���g�J���[����Z��������
		
	    float attenuation0;     // �����ɂ�錸�������p�p�����[�^�O
	    float attenuation1;     // �����ɂ�錸�������p�p�����[�^�P
	    float attenuation2;     // �����ɂ�錸�������p�p�����[�^�Q
	    float padding2;         // �p�f�B���O�Q
	};

	// �s�N�Z���V�F�[�_�[�E���_�V�F�[�_�[���ʃp�����[�^
	struct Common
	{
	    Light light[DX_D3D11_COMMON_CONST_LIGHT_NUM];   // ���C�g�p�����[�^
	    Material material;                              // �}�e���A���p�����[�^
	    VsFog fog;                                      // �t�H�O�p�����[�^
	};

#endif
