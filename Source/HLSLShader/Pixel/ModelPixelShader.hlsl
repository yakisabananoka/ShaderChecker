#include "PixelShader3DHeader.hlsli"

PS_OUTPUT main(PS_INPUT input) : SV_TARGET
{
    float4 result = float4(1.0f, 1.0f, 1.0f, 1.0f);

    //テクスチャがある場合はそれを考慮した処理を行う
    uint2 diffuseMapSize;
    diffuseMapTexture.GetDimensions(diffuseMapSize.x, diffuseMapSize.y);
    if(diffuseMapSize.x * diffuseMapSize.y > 0)
    {
        float4 texColor = diffuseMapTexture.Sample(diffuseMapSampler, input.uv);
        if (texColor.a == 0.0f)
        {
            discard;
        }
        
        result *= texColor;
    }

    const float3 ray = normalize(input.viewPos);            //カメラ→自身のベクトル
    const float3 normal = normalize(input.viewNorm);        //法線(ビュー)

    //ライティング処理での合計色
    float3 totalDiffuse = float3(0, 0, 0);
    float3 totalSpecular = float3(0, 0, 0);

    //ライトごとにライティング処理
    for (int i = 0; i < DX_D3D11_COMMON_CONST_LIGHT_NUM; i++)
    {
        ProcessLight(input.viewPos, ray, normal, common.light[i], common.material, totalDiffuse, totalSpecular);
    }
    
    totalDiffuse += common.material.ambientEmissive.rgb;
    totalSpecular *= common.material.specular.rgb;

    result.rgb *= totalDiffuse;
    result.rgb += totalSpecular;
    result.a *= common.material.diffuse.a * base.factorColor.a;

    result.rgb += base.drawAddColor.rgb;

    return saturate(result);
}
