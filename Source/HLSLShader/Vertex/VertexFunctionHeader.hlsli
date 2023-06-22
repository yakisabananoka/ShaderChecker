//インクルードガード
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
    //ライトの位置(ワールド)
    const float3 lightPos = GetLightWorldPos(light, pos);
    
    //ライトの方向
    const float3 lightRay = normalize(pos - lightPos);
    
    //ライトとの距離
    const float lightDistance = distance(pos, lightPos);
    
    float lightGen = 1.0f / (light.attenuation0 + light.attenuation1 * lightDistance + light.attenuation2 * pow(lightDistance, 2.0f));
    lightGen *= smoothstep(0.0f, 1.0f, (light.rangePow2 - pow(lightDistance, 2.0f)) / 10000000.0f);
    
    totalDiffuse += (light.diffuse * common.material.diffuse.rgb * GetDiffuse(normal, lightRay) + light.ambient.rgb) * lightGen;
    
    totalSpecular += GetSpecular(lightRay, normal, ray) * light.specular;
}

void SpotLightProcess(float3 pos, Light light, float3 ray, float3 normal, inout float3 totalDiffuse, inout float3 totalSpecular)
{
    //ライトの位置(ワールド)
    const float3 lightPos = GetLightWorldPos(light, pos);
    
    //ライトのベクトル(ワールド)
    const float3 lightDir = GetLightWorldDir(light);
    
    //頂点とライトのベクトルを算出
    const float3 lightRay = normalize(pos - lightPos);
    
    //ライトとの距離を算出
    const float lightDistance = abs(distance(pos, lightPos));
    
    //距離による減衰率の計算
    float lightGen = 1.0f / (light.attenuation0 + light.attenuation1 * lightDistance + light.attenuation2 * pow(lightDistance, 2.0f));
    
    //ライトベクトルとライトから頂点へのベクトルの内積を算出
    const float lightDirectionCosA = dot(lightRay, lightDir);
    
    //スポットライトとしての減衰率の計算
    lightGen *= saturate(pow(abs(max(lightDirectionCosA - light.spotParam0, 0.0f) * light.spotParam1), light.fallOff));
    
    //有効距離外なら減衰率を最大
    //lightGen *= step(pow(lightDistance, 2.0f), light.rangePow2);
    lightGen *= smoothstep(0.0f, 1.0f, (light.rangePow2 - pow(lightDistance, 2.0f)) / 10000000.0f);
    
    //減衰率の計算    
    totalDiffuse += (light.diffuse * common.material.diffuse.rgb * GetDiffuse(normal, lightRay) + light.ambient.rgb) * lightGen;
    
    totalSpecular += GetSpecular(lightRay, normal, ray) * light.specular;
}

void OldSpotLightProcess(float3 pos, Light light, float3 ray, float3 normal, inout float3 totalDiffuse, inout float3 totalSpecular)
{
    //ライトの位置(ワールド)
    const float3 lightPos = GetLightWorldPos(light, pos);
    
    //ライトのベクトル(ワールド)
    const float3 lightDir = GetLightWorldDir(light);
    
    //頂点とライトのベクトルを算出
    const float3 lightRay = normalize(pos - lightPos);
    
    //ライトとの距離を算出
    const float lightDistance = abs(distance(pos, lightPos));
    
    //距離による減衰率の計算
    float lightGen = 1.0f / (light.attenuation0 + light.attenuation1 * lightDistance + light.attenuation2 * pow(lightDistance, 2.0f));
    
    //ライトベクトルとライトから頂点へのベクトルの内積を算出
    const float lightDirectionCosA = dot(lightRay, lightDir);
    
    //スポットライトとしての減衰率の計算
    lightGen *= saturate(pow(abs(max(lightDirectionCosA - light.spotParam0, 0.0f) * light.spotParam1), light.fallOff));
    
    //有効距離外なら減衰率を最大
    lightGen *= step(pow(lightDistance, 2.0f), light.rangePow2);
    
    //減衰率の計算    
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
        //ポイントライト
        PointLightProcess(pos, light, ray, normal, totalDiffuse, totalSpecular);
    }
    else if (light.type == DX_LIGHTTYPE_SPOT)
    {
        //スポットライト
        SpotLightProcess(pos, light, ray, normal, totalDiffuse, totalSpecular);
    }
    else if (light.type == DX_LIGHTTYPE_DIRECTIONAL)
    {
        //ディレクショナルライト
        DirectionalLightProcess(pos, light, ray, normal, totalDiffuse, totalSpecular);
    }

}

#endif

