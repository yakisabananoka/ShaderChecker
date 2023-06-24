//�C���N���[�h�K�[�h
#if !defined(VERTEX_STRUCTURES_HEADER)
	#define VERTEX_STRUCTURES_HEADER

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
	    float4x4 shadowMapLightViewProjectionMatrix[3];					// �V���h�E�}�b�v�p�̃��C�g�r���[�s��ƃ��C�g�ˉe�s�����Z��������
	    float4x2 textureMatrix[DX_D3D11_VS_CONST_TEXTURE_MATRIX_NUM];	// �e�N�X�`�����W����p�s��
	};

	// �X�L�j���O���b�V���p�́@���[�J���@���@���[���h�s��
	struct VsLocalWorldMatrix
	{
	    float4 lwMatrix[DX_D3D11_VS_CONST_WORLD_MAT_NUM * 3];           // ���[�J���@���@���[���h�s��
	};

#endif
