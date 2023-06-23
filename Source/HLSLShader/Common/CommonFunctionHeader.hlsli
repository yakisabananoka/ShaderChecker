//インクルードガード
#if !defined(COMMON_FUNCTION_HEADER)
	#define COMMON_FUNCTION_HEADER

	#include "CommonStructuresHeader.hlsli"

	/// @brief 拡散反射の強さを計算
	/// @param lightRay ライトのレイ
	/// @param normal 法線
	/// @return 
	float CalculateDiffuse(float3 lightRay, float3 normal)
	{
	    return saturate(dot(normal, -lightRay));
	}

	/// @brief 鏡面反射の強さを計算
	/// @param lightRay ライトのレイ
	/// @param normal 法線
	/// @param cameraRay レイ
	/// @param power 強さ
	/// @return 
	float CalculateSpecular(float3 lightRay, float3 normal, float3 cameraRay, float power)
	{
	    return pow(saturate(dot(-cameraRay, reflect(lightRay, normal))), power);
	}

	/// @brief ポイントライトの処理
	/// @param pos 位置(ビュー)
	/// @param cameraRay レイ(ビュー)
	/// @param normal 法線(ビュー)
	/// @param light ライト構造体
	/// @param material マテリアル
	/// @param totalDiffuse 拡散反射入出力
	/// @param totalSpecular 鏡面反射入出力
	void ProcessPointLight(float3 pos, float3 cameraRay, float3 normal, Light light, Material material, inout float3 totalDiffuse, inout float3 totalSpecular)
	{
		//ライトから位置へのベクトルを算出
	    const float3 lightRay = normalize(pos - light.position);

	    //ライトとの距離
	    const float lightDistance = distance(pos, light.position);
	    
	    float lightDecay = 1.0f / (light.attenuation0 + light.attenuation1 * lightDistance + light.attenuation2 * pow(lightDistance, 2.0f));
	    lightDecay *= smoothstep(0.0f, 1.0f, (light.rangePow2 - pow(lightDistance, 2.0f)) / 10000000.0f);
	    
	    totalDiffuse += (light.diffuse * material.diffuse.rgb * CalculateDiffuse(lightRay, normal) + light.ambient.rgb) * lightDecay;
	    
	    totalSpecular += CalculateSpecular(light.direction, normal, cameraRay, material.power) * light.specular;
	}

	/// @brief スポットライトの処理
	/// @param pos 位置(ビュー)
	/// @param ray レイ(ビュー)
	/// @param normal 法線(ビュー)
	/// @param light ライト構造体
	/// @param material マテリアル
	/// @param totalDiffuse 拡散反射入出力
	/// @param totalSpecular 鏡面反射入出力
	void ProcessSpotLight(float3 pos, float3 ray, float3 normal, Light light, Material material, inout float3 totalDiffuse, inout float3 totalSpecular)
	{
	    //ライトから位置へのベクトルを算出
	    const float3 lightRay = normalize(pos - light.position);
	    
	    //ライトとの距離を算出
	    const float lightDistance = abs(distance(pos, light.position));
	    
	    //距離による減衰率の計算
	    float lightDecay = 1.0f / (light.attenuation0 + light.attenuation1 * lightDistance + light.attenuation2 * pow(lightDistance, 2.0f));
	    
	    //ライトベクトルとライトから頂点へのベクトルの内積を算出
	    const float lightDirectionCosA = dot(lightRay, light.direction);
	    
	    //スポットライトとしての減衰率の計算
	    lightDecay *= saturate(pow(abs(max(lightDirectionCosA - light.spotParam0, 0.0f) * light.spotParam1), light.fallOff));
	    
	    //有効距離外なら減衰率を最大
	    //lightDecay *= step(pow(lightDistance, 2.0f), light.rangePow2);                                        //境界がはっきりしている
	    lightDecay *= smoothstep(0.0f, 1.0f, (light.rangePow2 - pow(lightDistance, 2.0f)) / 10000000.0f);       //境界が曖昧
	    
	    //減衰率の計算    
	    totalDiffuse += (light.diffuse * material.diffuse.rgb * CalculateDiffuse(lightRay, normal) + light.ambient.rgb) * lightDecay;
	    totalSpecular += CalculateSpecular(lightRay, normal, ray, material.power) * light.specular;
	}

	/// @brief ディレクショナルライトの処理
	/// @param pos 位置(ビュー)
	/// @param ray レイ(ビュー)
	/// @param normal 法線(ビュー)
	/// @param light ライト構造体
	/// @param material マテリアル
	/// @param totalDiffuse 拡散反射入出力
	/// @param totalSpecular 鏡面反射入出力
	void ProcessDirectionalLight(float3 pos, float3 ray, float3 normal, Light light, Material material, inout float3 totalDiffuse, inout float3 totalSpecular)
	{
	    totalDiffuse += light.diffuse * material.diffuse.rgb * CalculateDiffuse(light.direction, normal) + light.ambient.rgb;
	    
	    totalSpecular += CalculateSpecular(light.direction, normal, ray, material.power) * light.specular;
	}

	/// @brief 種類を問わないライトの処理
	/// @param pos 位置(ビュー)
	/// @param ray レイ(ビュー)
	/// @param normal 法線(ビュー)
	/// @param light ライト構造体
	/// @param material マテリアル
	/// @param totalDiffuse 拡散反射入出力
	/// @param totalSpecular 鏡面反射入出力
	void ProcessLight(float3 pos, float3 ray, float3 normal, Light light, Material material, inout float3 totalDiffuse, inout float3 totalSpecular)
	{
	    if (light.type == DX_LIGHTTYPE_POINT)
	    {
	        //ポイントライト
	        ProcessPointLight(pos, ray, normal, light, material, totalDiffuse, totalSpecular);
	    }
	    else if (light.type == DX_LIGHTTYPE_SPOT)
	    {
	        //スポットライト
	        ProcessSpotLight(pos, ray, normal, light, material, totalDiffuse, totalSpecular);
	    }
	    else if (light.type == DX_LIGHTTYPE_DIRECTIONAL)
	    {
	        //ディレクショナルライト
	        ProcessDirectionalLight(pos, ray, normal, light, material, totalDiffuse, totalSpecular);
	    }
	}

#endif
