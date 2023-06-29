//�C���N���[�h�K�[�h
#if !defined(COMMON_FUNCTION_HEADER)
	#define COMMON_FUNCTION_HEADER

	#include "CommonStructuresHeader.hlsli"

	/// @brief �e�v�f�̓��A�ő�l�̗v�f��Ԃ�
	/// @param vec �C�ӂ̃x�N�g��
	/// @return �ő�l�̗v�f
	float VecMax(in float3 vec)
	{
	    return max(vec.r, max(vec.g, vec.b));
	}

	/// @brief �e�v�f�̓��A�ŏ��l�̗v�f��Ԃ�
	/// @param vec �C�ӂ̃x�N�g��
	/// @return �ŏ��l�̗v�f
	float VecMin(in float3 vec)
	{
	    return min(vec.r, min(vec.g, vec.b));
	}

	/// @brief RGB����HSV�ɕϊ�
	/// @param color RGB
	/// @return HSV
	float3 RGBtoHSV(in float3 color)
	{
		const float3 clampedColor = saturate(color);

	    float3 result = float3(0.f, 0.f, 0.f);

	    const float maxValue = VecMax(clampedColor);
	    const float minValue = VecMin(clampedColor);

	    const float delta = maxValue - minValue;

		//H(�F��)�̐ݒ�
		if(delta > 0.0f)
	    {
	        if (maxValue == clampedColor.r)
			{
	            result.r = (clampedColor.g - clampedColor.b) / delta;
	        }
	        else if (maxValue == clampedColor.g)
			{
	            result.r = (clampedColor.b - clampedColor.r) / delta + 2.f;
	        }
			else
			{
	            result.r = (clampedColor.r - clampedColor.g) / delta + 4.f;
	        }

	        result.r /= 6.f;
			if(result.r < 0.0f)
			{
	            result.r += 1.f;
	        }
	    }

		//S(�ʓx)�̐ݒ�
		if(maxValue != 0.0f)
	    {
	        result.g = delta / maxValue;
	    }

		//V(���x)�̐ݒ�
		result.b = maxValue;

	    return result;
	}

	/// @brief HSV����RGB�ɕϊ�
	/// @param color HSV
	/// @return RGB
	float3 HSVtoRGB(in float3 color)
	{
		float3 clampedColor = saturate(color);
	    float3 result = float3(clampedColor.b, clampedColor.b, clampedColor.b);

		if(clampedColor.g != 0.0f)
		{
	        clampedColor.r *= 6.f;
	        const float f = clampedColor.r - floor(clampedColor.r);
	        const float a = clampedColor.b * (1 - clampedColor.g);
	        const float b = clampedColor.b * (1 - clampedColor.g * f);
	        const float c = clampedColor.b * (1 - clampedColor.g * (1 - f));

			if(clampedColor.r < 1)
			{
	            result.r = clampedColor.b;
	            result.g = c;
	            result.b = a;
	        }
			else if(clampedColor.r < 2)
			{
	            result.r = b;
	            result.g = clampedColor.b;
	            result.b = a;
	        }
	        else if (clampedColor.r < 3)
	        {
	            result.r = a;
	            result.g = clampedColor.b;
	            result.b = c;
	        }
	        else if (clampedColor.r < 4)
	        {
	            result.r = a;
	            result.g = b;
	            result.b = clampedColor.b;
	        }
	        else if (clampedColor.r < 5)
	        {
	            result.r = c;
	            result.g = a;
	            result.b = clampedColor.b;
	        }
	        else
	        {
	            result.r = clampedColor.b;
	            result.g = a;
	            result.b = b;
	        }
	    }

	    return result;
	}

	/// @brief XorShift�@�ł̋^����������
	/// @param seed �V�[�h�l
	/// @return �^������
	uint XorShift(in uint seed)
	{
	    uint ret = seed;
	    ret ^= ret << 13;
	    ret ^= ret >> 17;
	    ret ^= ret << 5;
	    return ret;
	}

	/// @brief �x�N�g����ԕϊ�
	/// @param vec �x�N�g��
	/// @param tan ���̋�Ԃ�X�����P�ʃx�N�g����ϊ����Ԃɕϊ���������
	/// @param bin ���̋�Ԃ�Y�����P�ʃx�N�g����ϊ����Ԃɕϊ���������
	/// @param norm ���̋�Ԃ�Z�����P�ʃx�N�g����ϊ����Ԃɕϊ���������
	/// @return �ϊ���̃x�N�g��
	float3 ConvertCoordinateSpace(in float3 vec, in float3 tan, in float3 bin, in float3 norm)
	{
		//�r���[���W�n�ɕϊ�����t�s����擾
	    const float3x3 tangentViewMat = transpose(float3x3(normalize(tan), normalize(bin), normalize(norm)));

		//�x�N�g�����r���[���W�n�ɕϊ�
	    return normalize(mul(tangentViewMat, vec));
	}

	/// @brief �g�U���˂̋������v�Z
	/// @param lightRay ���C�g�̃��C
	/// @param normal �@��
	/// @return 
	float CalculateDiffuse(in float3 lightRay, in float3 normal)
	{
	    return saturate(dot(normal, -lightRay));
	}

	/// @brief ���ʔ��˂̋������v�Z
	/// @param lightRay ���C�g�̃��C
	/// @param normal �@��
	/// @param cameraRay ���C
	/// @param power ����
	/// @return 
	float CalculateSpecular(in float3 lightRay, in float3 normal, in float3 cameraRay, in float power)
	{
		//�Ō��step�֐��Ŋђʂ�h��
		return pow(saturate(dot(normal, -normalize(cameraRay + lightRay))), power) * step(0.0f, dot(normal, -lightRay));	//Blinn-Phong(DX���C�u�����͂�������̗p)
	    //return pow(saturate(dot(-cameraRay, reflect(lightRay, normal))), power);											//Phong
	}

	/// @brief �|�C���g���C�g�̏���
	/// @param pos �ʒu(�r���[)
	/// @param cameraRay ���C(�r���[)
	/// @param normal �@��(�r���[)
	/// @param light ���C�g�\����
	/// @param power ���ʔ��˂̋���
	/// @param totalDiffuse �g�U���˓��o��
	/// @param totalSpecular ���ʔ��˓��o��
	void ProcessPointLight(in float3 pos, in float3 cameraRay, in float3 normal, in Light light, in float power, inout float3 totalDiffuse, inout float3 totalSpecular)
	{
		//���C�g����ʒu�ւ̃x�N�g�����Z�o
	    const float3 lightRay = normalize(pos - light.position);

	    //���C�g�Ƃ̋���
	    const float lightDistance = distance(pos, light.position);

		//���C�g�̌������v�Z
	    float lightDecay = 1.0f / (light.attenuation0 + light.attenuation1 * lightDistance + light.attenuation2 * pow(lightDistance, 2.0f));

		//�L�������O�Ȃ猸�������ő�
		lightDecay *= step(pow(lightDistance, 2.0f), light.rangePow2);

		//�ŏI�I�Ȍ��ʂɉ��Z
	    totalDiffuse += (CalculateDiffuse(lightRay, normal) * light.diffuse + light.ambient.rgb) * lightDecay;
	    totalSpecular += CalculateSpecular(lightRay, normal, cameraRay, power) * light.specular * lightDecay;
	}

	/// @brief �X�|�b�g���C�g�̏���
	/// @param pos �ʒu(�r���[)
	/// @param ray ���C(�r���[)
	/// @param normal �@��(�r���[)
	/// @param light ���C�g�\����
	/// @param power ���ʔ��˂̋���
	/// @param totalDiffuse �g�U���˓��o��
	/// @param totalSpecular ���ʔ��˓��o��
	void ProcessSpotLight(in float3 pos, in float3 ray, in float3 normal, in Light light, in float power, inout float3 totalDiffuse, inout float3 totalSpecular)
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
	    lightDecay *= step(pow(lightDistance, 2.0f), light.rangePow2);
	    
	    //�ŏI�I�Ȍ��ʂɉ��Z  
		totalDiffuse += (CalculateDiffuse(lightRay, normal) * light.diffuse + light.ambient.rgb) * lightDecay;
	    totalSpecular += CalculateSpecular(lightRay, normal, ray, power) * light.specular * lightDecay;
	}

	/// @brief �f�B���N�V���i�����C�g�̏���
	/// @param pos �ʒu(�r���[)
	/// @param cameraRay ���C(�r���[)
	/// @param normal �@��(�r���[)
	/// @param light ���C�g�\����
	/// @param power ���ʔ��˂̋���
	/// @param totalDiffuse �g�U���˓��o��
	/// @param totalSpecular ���ʔ��˓��o��
	void ProcessDirectionalLight(in float3 pos, in float3 cameraRay, in float3 normal, in Light light, in float power, inout float3 totalDiffuse, inout float3 totalSpecular)
	{
		//�ŏI�I�Ȍ��ʂɉ��Z
	    totalDiffuse += CalculateDiffuse(light.direction, normal) * light.diffuse  + light.ambient.rgb;
	    totalSpecular += CalculateSpecular(light.direction, normal, cameraRay, power) * light.specular;
	}

	/// @brief ��ނ���Ȃ����C�g�̏���
	/// @param pos �ʒu(�r���[)
	/// @param cameraRay ���C(�r���[)
	/// @param normal �@��(�r���[)
	/// @param light ���C�g�\����
	/// @param power ���ʔ��˂̋���
	/// @param totalDiffuse �g�U���˓��o��
	/// @param totalSpecular ���ʔ��˓��o��
	void ProcessLight(in float3 pos, in float3 cameraRay, in float3 normal, in Light light, in float power, inout float3 totalDiffuse, inout float3 totalSpecular)
	{
	    if (light.type == DX_LIGHTTYPE_POINT)
	    {
	        //�|�C���g���C�g
	        ProcessPointLight(pos, cameraRay, normal, light, power, totalDiffuse, totalSpecular);
	    }
	    else if (light.type == DX_LIGHTTYPE_SPOT)
	    {
	        //�X�|�b�g���C�g
	        ProcessSpotLight(pos, cameraRay, normal, light, power, totalDiffuse, totalSpecular);
	    }
	    else if (light.type == DX_LIGHTTYPE_DIRECTIONAL)
	    {
	        //�f�B���N�V���i�����C�g
	        ProcessDirectionalLight(pos, cameraRay, normal, light, power, totalDiffuse, totalSpecular);
	    }
	}

#endif
