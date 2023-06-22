#include "PixelShader3DHeader.hlsli"

PS_OUTPUT main(PS_INPUT input) : SV_TARGET
{
    float4 result = input.diffuse;
    if(result.a == 0.0f)
    {
        discard;
    }

    uint2 diffuseMapSize;
    diffuseMapTexture.GetDimensions(diffuseMapSize.x, diffuseMapSize.y);
    if(diffuseMapSize.x * diffuseMapSize.y>0)
    {
        float4 texColor = diffuseMapTexture.Sample(diffuseMapSampler, input.uv);
        if (texColor.a == 0.0f)
        {
            discard;
        }
        
        result *= texColor;
    }
    
    const float3 ray = normalize(input.viewPos);
    const float3 normal = normalize(input.viewNorm);
    
    float3 totalDiffuse = float3(0, 0, 0);
    float3 totalSpecular = float3(0, 0, 0);
    
    for (int i = 0; i < DX_D3D11_COMMON_CONST_LIGHT_NUM; i++)
    {
        ProcessLight(input.viewPos, ray, normal, common.light[i], common.material, totalDiffuse, totalSpecular);
    }
    
    totalDiffuse = totalDiffuse * input.diffuse.rgb + common.material.ambientEmissive.rgb;
    totalSpecular *= common.material.specular.rgb;
    
    float3 rgb = result.rgb * totalDiffuse + totalSpecular;

    //float alpha = texColor.a * common.material.diffuse.a * base.factorColor.a;
    
    return float4(rgb, 1.0f);
}
