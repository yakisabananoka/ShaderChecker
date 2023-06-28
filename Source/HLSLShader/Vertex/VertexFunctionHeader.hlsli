//�C���N���[�h�K�[�h
#if !defined(VERTEX_FUNCTION_HEADER)
	#define VERTEX_FUNCTION_HEADER

	#include "../Common/CommonFunctionHeader.hlsli"
	#include "VertexStructuresHeader.hlsli"

	/// @brief ���[�J�������[���h�̃u�����h�s��̍쐬
	/// @param indices �{�[�������p�C���f�b�N�X
	/// @param weight �{�[�������p�E�F�C�g
	/// @param localWorldMatrix ���[�J�������[���h�̍s��
	/// @param mat �u�����h�s��̓��o��
	void CalculateLocalWorldMatrixImplement(in float4 indices, in float4 weight, in VsLocalWorldMatrix localWorldMatrix, inout float3x4 mat)
	{
	    mat[0] += localWorldMatrix.lwMatrix[indices.x + 0] * weight.x;
		mat[0] += localWorldMatrix.lwMatrix[indices.y + 0] * weight.y;
		mat[0] += localWorldMatrix.lwMatrix[indices.z + 0] * weight.z;
		mat[0] += localWorldMatrix.lwMatrix[indices.w + 0] * weight.w;

	    mat[1] += localWorldMatrix.lwMatrix[indices.x + 1] * weight.x;
	    mat[1] += localWorldMatrix.lwMatrix[indices.y + 1] * weight.y;
	    mat[1] += localWorldMatrix.lwMatrix[indices.z + 1] * weight.z;
	    mat[1] += localWorldMatrix.lwMatrix[indices.w + 1] * weight.w;

	    mat[2] += localWorldMatrix.lwMatrix[indices.x + 2] * weight.x;
	    mat[2] += localWorldMatrix.lwMatrix[indices.y + 2] * weight.y;
	    mat[2] += localWorldMatrix.lwMatrix[indices.z + 2] * weight.z;
	    mat[2] += localWorldMatrix.lwMatrix[indices.w + 2] * weight.w;
	}

	/// @brief ���[�J�������[���h�̃u�����h�s��̍쐬(1�`4�t���[���̉e�����󂯂钸�_�����ꍇ)
	/// @param indices �{�[�������p�C���f�b�N�X
	/// @param weight �{�[�������p�E�F�C�g
	/// @param localWorldMatrix ���[�J�������[���h�̍s��
	/// @return �u�����h�s��
	float4x3 CalculateLocalWorldMatrix(in float4 indices, in float4 weight, in VsLocalWorldMatrix localWorldMatrix)
	{
	    float3x4 mat = float3x4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		CalculateLocalWorldMatrixImplement(indices, weight, localWorldMatrix, mat);
		return transpose(mat);
	}

	/// @brief ���[�J�������[���h�̃u�����h�s��̍쐬(5�`8�t���[���̉e�����󂯂钸�_�����ꍇ)
	/// @param indices0 �{�[�������p�C���f�b�N�X0
	/// @param weight0 �{�[�������p�E�F�C�g0
	/// @param indices1 �{�[�������p�C���f�b�N�X1
	/// @param weight1 �{�[�������p�E�F�C�g1
	/// @param localWorldMatrix ���[�J�������[���h�̍s��
	/// @return �u�����h�s��
	float4x3 CalculateLocalWorldMatrix(in float4 indices0, in float4 weight0, in float4 indices1, in float4 weight1, in VsLocalWorldMatrix localWorldMatrix)
	{
		float3x4 mat = float3x4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		CalculateLocalWorldMatrixImplement(indices0, weight0, localWorldMatrix, mat);
	    CalculateLocalWorldMatrixImplement(indices1, weight1, localWorldMatrix, mat);
	    return transpose(mat);
	}

#endif

