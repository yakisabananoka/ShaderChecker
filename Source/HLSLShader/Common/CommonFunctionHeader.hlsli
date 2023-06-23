//�C���N���[�h�K�[�h
#if !defined(COMMON_FUNCTION_HEADER)
	#define COMMON_FUNCTION_HEADER

	#include "CommonStructuresHeader.hlsli"

	/// @brief �g�U���˂̋������v�Z
	/// @param lightRay ���C�g�̃��C
	/// @param normal �@��
	/// @return 
	float CalculateDiffuse(float3 lightRay, float3 normal)
	{
	    return saturate(dot(normal, -lightRay));
	}

	/// @brief ���ʔ��˂̋������v�Z
	/// @param lightRay ���C�g�̃��C
	/// @param normal �@��
	/// @param cameraRay ���C
	/// @param power ����
	/// @return 
	float CalculateSpecular(float3 lightRay, float3 normal, float3 cameraRay, float power)
	{
	    return pow(saturate(dot(-cameraRay, reflect(lightRay, normal))), power);
	}

	/// @brief �|�C���g���C�g�̏���
	/// @param pos �ʒu(�r���[)
	/// @param cameraRay ���C(�r���[)
	/// @param normal �@��(�r���[)
	/// @param light ���C�g�\����
	/// @param material �}�e���A��
	/// @param totalDiffuse �g�U���˓��o��
	/// @param totalSpecular ���ʔ��˓��o��
	void ProcessPointLight(float3 pos, float3 cameraRay, float3 normal, Light light, Material material, inout float3 totalDiffuse, inout float3 totalSpecular)
	{
		//���C�g����ʒu�ւ̃x�N�g�����Z�o
	    const float3 lightRay = normalize(pos - light.position);

	    //���C�g�Ƃ̋���
	    const float lightDistance = distance(pos, light.position);
	    
	    float lightDecay = 1.0f / (light.attenuation0 + light.attenuation1 * lightDistance + light.attenuation2 * pow(lightDistance, 2.0f));
	    lightDecay *= smoothstep(0.0f, 1.0f, (light.rangePow2 - pow(lightDistance, 2.0f)) / 10000000.0f);
	    
	    totalDiffuse += (light.diffuse * material.diffuse.rgb * CalculateDiffuse(lightRay, normal) + light.ambient.rgb) * lightDecay;
	    
	    totalSpecular += CalculateSpecular(light.direction, normal, cameraRay, material.power) * light.specular;
	}

	/// @brief �X�|�b�g���C�g�̏���
	/// @param pos �ʒu(�r���[)
	/// @param ray ���C(�r���[)
	/// @param normal �@��(�r���[)
	/// @param light ���C�g�\����
	/// @param material �}�e���A��
	/// @param totalDiffuse �g�U���˓��o��
	/// @param totalSpecular ���ʔ��˓��o��
	void ProcessSpotLight(float3 pos, float3 ray, float3 normal, Light light, Material material, inout float3 totalDiffuse, inout float3 totalSpecular)
	{
	    //���C�g����ʒu�ւ̃x�N�g�����Z�o
	    const float3 lightRay = normalize(pos - light.position);
	    
	    //���C�g�Ƃ̋������Z�o
	    const float lightDistance = abs(distance(pos, light.position));
	    
	    //�����ɂ�錸�����̌v�Z
	    float lightDecay = 1.0f / (light.attenuation0 + light.attenuation1 * lightDistance + light.attenuation2 * pow(lightDistance, 2.0f));
	    
	    //���C�g�x�N�g���ƃ��C�g���璸�_�ւ̃x�N�g���̓��ς��Z�o
	    const float lightDirectionCosA = dot(lightRay, light.direction);
	    
	    //�X�|�b�g���C�g�Ƃ��Ă̌������̌v�Z
	    lightDecay *= saturate(pow(abs(max(lightDirectionCosA - light.spotParam0, 0.0f) * light.spotParam1), light.fallOff));
	    
	    //�L�������O�Ȃ猸�������ő�
	    //lightDecay *= step(pow(lightDistance, 2.0f), light.rangePow2);                                        //���E���͂����肵�Ă���
	    lightDecay *= smoothstep(0.0f, 1.0f, (light.rangePow2 - pow(lightDistance, 2.0f)) / 10000000.0f);       //���E���B��
	    
	    //�������̌v�Z    
	    totalDiffuse += (light.diffuse * material.diffuse.rgb * CalculateDiffuse(lightRay, normal) + light.ambient.rgb) * lightDecay;
	    totalSpecular += CalculateSpecular(lightRay, normal, ray, material.power) * light.specular;
	}

	/// @brief �f�B���N�V���i�����C�g�̏���
	/// @param pos �ʒu(�r���[)
	/// @param ray ���C(�r���[)
	/// @param normal �@��(�r���[)
	/// @param light ���C�g�\����
	/// @param material �}�e���A��
	/// @param totalDiffuse �g�U���˓��o��
	/// @param totalSpecular ���ʔ��˓��o��
	void ProcessDirectionalLight(float3 pos, float3 ray, float3 normal, Light light, Material material, inout float3 totalDiffuse, inout float3 totalSpecular)
	{
	    totalDiffuse += light.diffuse * material.diffuse.rgb * CalculateDiffuse(light.direction, normal) + light.ambient.rgb;
	    
	    totalSpecular += CalculateSpecular(light.direction, normal, ray, material.power) * light.specular;
	}

	/// @brief ��ނ���Ȃ����C�g�̏���
	/// @param pos �ʒu(�r���[)
	/// @param ray ���C(�r���[)
	/// @param normal �@��(�r���[)
	/// @param light ���C�g�\����
	/// @param material �}�e���A��
	/// @param totalDiffuse �g�U���˓��o��
	/// @param totalSpecular ���ʔ��˓��o��
	void ProcessLight(float3 pos, float3 ray, float3 normal, Light light, Material material, inout float3 totalDiffuse, inout float3 totalSpecular)
	{
	    if (light.type == DX_LIGHTTYPE_POINT)
	    {
	        //�|�C���g���C�g
	        ProcessPointLight(pos, ray, normal, light, material, totalDiffuse, totalSpecular);
	    }
	    else if (light.type == DX_LIGHTTYPE_SPOT)
	    {
	        //�X�|�b�g���C�g
	        ProcessSpotLight(pos, ray, normal, light, material, totalDiffuse, totalSpecular);
	    }
	    else if (light.type == DX_LIGHTTYPE_DIRECTIONAL)
	    {
	        //�f�B���N�V���i�����C�g
	        ProcessDirectionalLight(pos, ray, normal, light, material, totalDiffuse, totalSpecular);
	    }
	}

#endif
