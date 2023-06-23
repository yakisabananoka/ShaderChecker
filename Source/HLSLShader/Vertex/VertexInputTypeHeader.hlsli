//�C���N���[�h�K�[�h
#if !defined(VERTEX_INPUT_TYPE_HEADER)
	#define VERTEX_INPUT_TYPE_HEADER

	//�ʏ�̃��f��
	#define VERTEX_INPUT_TYPE_1FRAME		(1)		//1�t���[���̉e�����󂯂钸�_
	#define VERTEX_INPUT_TYPE_4FRAME		(2)		//1�`4�t���[���̉e�����󂯂钸�_
	#define VERTEX_INPUT_TYPE_8FRAME		(3)		//5�`8�t���[���̉e�����󂯂钸�_

	//�@���}�b�v�t��
	#define VERTEX_INPUT_TYPE_NMAP_1FRAME	(4)		//�@���}�b�v�̏�񂪊܂܂��1�t���[���̉e�����󂯂钸�_
	#define VERTEX_INPUT_TYPE_NMAP_4FRAME	(5)		//�@���}�b�v�̏�񂪊܂܂��1�`4�t���[���̉e�����󂯂钸�_
	#define VERTEX_INPUT_TYPE_NMAP_8FRAME	(6)		//�@���}�b�v�̏�񂪊܂܂��5�`8�t���[���̉e�����󂯂钸�_

	//VERTEX3DSHADER�\����
	#define VERTEX_INPUT_TYPE_ORIGIN		(7)		//DrawPolygon3D�֐������g�p�����ꍇ�ɑ����钸�_

	//�ȉ��ADX���C�u������̕\�L
	//�ʏ�̃��f��
	#define DX_MV1_VERTEX_TYPE_1FRAME	VERTEX_INPUT_TYPE_1FRAME
	#define DX_MV1_VERTEX_TYPE_4FRAME	VERTEX_INPUT_TYPE_4FRAME
	#define DX_MV1_VERTEX_TYPE_8FRAME   VERTEX_INPUT_TYPE_8FRAME

	//�@���}�b�v�t��
	#define DX_MV1_VERTEX_TYPE_NMAP_1FRAME	VERTEX_INPUT_TYPE_NMAP_1FRAME
	#define DX_MV1_VERTEX_TYPE_NMAP_4FRAME	VERTEX_INPUT_TYPE_NMAP_4FRAME
	#define DX_MV1_VERTEX_TYPE_NMAP_8FRAME	VERTEX_INPUT_TYPE_NMAP_8FRAME

#endif
