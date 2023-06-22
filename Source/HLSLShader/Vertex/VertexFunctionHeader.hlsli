//�C���N���[�h�K�[�h
#if !defined(VERTEX_FUNCTION_HEADER)
#define VERTEX_FUNCTION_HEADER

#include "../Common/CommonFunctionHeader.hlsli"
#include "VertexShader3DHeader.hlsli"

float3 GetLightWorldPos(Light light, float3 pos)
{
    return mul(float4(light.position, 1.0f), g_drawMng.inverseViewMat).xyz;
}

float3 GetLightWorldDir(Light light)
{
    return normalize(mul(float4(light.direction, 0.0f), g_drawMng.inverseViewMat).xyz);
}

float GetDiffuse(float3 normal, float3 lightRay)
{
    return saturate(dot(normal, -lightRay));
}

float GetSpecular(float3 lightRay, float3 normal, float3 ray)
{
    return pow(saturate(dot(-ray, reflect(lightRay, normal))), common.material.power);
}

void PointLightProcess(float3 pos, Light light, float3 ray, float3 normal, inout float3 totalDiffuse, inout float3 totalSpecular)
{
    //���C�g�̈ʒu(���[���h)
    const float3 lightPos = GetLightWorldPos(light, pos);
    
    //���C�g�̕���
    const float3 lightRay = normalize(pos - lightPos);
    
    //���C�g�Ƃ̋���
    const float lightDistance = distance(pos, lightPos);
    
    float lightGen = 1.0f / (light.attenuation0 + light.attenuation1 * lightDistance + light.attenuation2 * pow(lightDistance, 2.0f));
    lightGen *= smoothstep(0.0f, 1.0f, (light.rangePow2 - pow(lightDistance, 2.0f)) / 10000000.0f);
    
    totalDiffuse += (light.diffuse * common.material.diffuse.rgb * GetDiffuse(normal, lightRay) + light.ambient.rgb) * lightGen;
    
    totalSpecular += GetSpecular(lightRay, normal, ray) * light.specular;
}

void SpotLightProcess(float3 pos, Light light, float3 ray, float3 normal, inout float3 totalDiffuse, inout float3 totalSpecular)
{
    //���C�g�̈ʒu(���[���h)
    const float3 lightPos = GetLightWorldPos(light, pos);
    
    //���C�g�̃x�N�g��(���[���h)
    const float3 lightDir = GetLightWorldDir(light);
    
    //���_�ƃ��C�g�̃x�N�g�����Z�o
    const float3 lightRay = normalize(pos - lightPos);
    
    //���C�g�Ƃ̋������Z�o
    const float lightDistance = abs(distance(pos, lightPos));
    
    //�����ɂ�錸�����̌v�Z
    float lightGen = 1.0f / (light.attenuation0 + light.attenuation1 * lightDistance + light.attenuation2 * pow(lightDistance, 2.0f));
    
    //���C�g�x�N�g���ƃ��C�g���璸�_�ւ̃x�N�g���̓��ς��Z�o
    const float lightDirectionCosA = dot(lightRay, lightDir);
    
    //�X�|�b�g���C�g�Ƃ��Ă̌������̌v�Z
    lightGen *= saturate(pow(abs(max(lightDirectionCosA - light.spotParam0, 0.0f) * light.spotParam1), light.fallOff));
    
    //�L�������O�Ȃ猸�������ő�
    //lightGen *= step(pow(lightDistance, 2.0f), light.rangePow2);
    lightGen *= smoothstep(0.0f, 1.0f, (light.rangePow2 - pow(lightDistance, 2.0f)) / 10000000.0f);
    
    //�������̌v�Z    
    totalDiffuse += (light.diffuse * common.material.diffuse.rgb * GetDiffuse(normal, lightRay) + light.ambient.rgb) * lightGen;
    
    totalSpecular += GetSpecular(lightRay, normal, ray) * light.specular;
}

void OldSpotLightProcess(float3 pos, Light light, float3 ray, float3 normal, inout float3 totalDiffuse, inout float3 totalSpecular)
{
    //���C�g�̈ʒu(���[���h)
    const float3 lightPos = GetLightWorldPos(light, pos);
    
    //���C�g�̃x�N�g��(���[���h)
    const float3 lightDir = GetLightWorldDir(light);
    
    //���_�ƃ��C�g�̃x�N�g�����Z�o
    const float3 lightRay = normalize(pos - lightPos);
    
    //���C�g�Ƃ̋������Z�o
    const float lightDistance = abs(distance(pos, lightPos));
    
    //�����ɂ�錸�����̌v�Z
    float lightGen = 1.0f / (light.attenuation0 + light.attenuation1 * lightDistance + light.attenuation2 * pow(lightDistance, 2.0f));
    
    //���C�g�x�N�g���ƃ��C�g���璸�_�ւ̃x�N�g���̓��ς��Z�o
    const float lightDirectionCosA = dot(lightRay, lightDir);
    
    //�X�|�b�g���C�g�Ƃ��Ă̌������̌v�Z
    lightGen *= saturate(pow(abs(max(lightDirectionCosA - light.spotParam0, 0.0f) * light.spotParam1), light.fallOff));
    
    //�L�������O�Ȃ猸�������ő�
    lightGen *= step(pow(lightDistance, 2.0f), light.rangePow2);
    
    //�������̌v�Z    
    totalDiffuse += (light.diffuse * common.material.diffuse.rgb * GetDiffuse(normal, lightRay) + light.ambient.rgb) * lightGen;
    
    totalSpecular += GetSpecular(lightRay, normal, ray) * light.specular;
}

void DirectionalLightProcess(float3 pos, Light light, float3 ray, float3 normal, inout float3 totalDiffuse, inout float3 totalSpecular)
{
    const float3 lightDir = GetLightWorldDir(light);
    
    totalDiffuse += light.diffuse * common.material.diffuse.rgb * GetDiffuse(normal, lightDir) + light.ambient.rgb;
    
    totalSpecular += GetSpecular(lightDir, normal, ray) * light.specular;
}

void LightSwitch(float3 pos, Light light, float3 ray, float3 normal, inout float3 totalDiffuse, inout float3 totalSpecular)
{
    if (light.type == DX_LIGHTTYPE_POINT)
    {
        //�|�C���g���C�g
        PointLightProcess(pos, light, ray, normal, totalDiffuse, totalSpecular);
    }
    else if (light.type == DX_LIGHTTYPE_SPOT)
    {
        //�X�|�b�g���C�g
        SpotLightProcess(pos, light, ray, normal, totalDiffuse, totalSpecular);
    }
    else if (light.type == DX_LIGHTTYPE_DIRECTIONAL)
    {
        //�f�B���N�V���i�����C�g
        DirectionalLightProcess(pos, light, ray, normal, totalDiffuse, totalSpecular);
    }

}

#endif

