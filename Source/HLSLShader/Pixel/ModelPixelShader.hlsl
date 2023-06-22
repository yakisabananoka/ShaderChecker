#include "PixelShader3DHeader.hlsli"

PS_OUTPUT main(PS_INPUT input) : SV_TARGET
{
    float4 texColor = diffuseMapTexture.Sample(diffuseMapSampler, input.uv);
    texColor.a = 1.0f;
    if (texColor.a == 0.0f)
    {
        discard;
    }
    
    if (input.diffuse.a == 0.0f)
    {
        discard;
    }
    
    float3 ray = normalize(input.viewPos);
    
    //float3 normal = normalize(input.);
    
    float3 totalDiffuse = float3(0, 0, 0);
    float3 totalSpecular = float3(0, 0, 0);
    
    for (int i = 0; i < DX_D3D11_COMMON_CONST_LIGHT_NUM; i++)
    {
        //LightSwitch(input.worldPos, common.light[i], ray, normal, totalDiffuse, totalSpecular);
    }
    
    totalDiffuse += input.diffuse.rgb + common.material.ambientEmissive.rgb;
    totalSpecular *= common.material.specular.rgb;
    
    float3 rgb = texColor.rgb * totalDiffuse + totalSpecular;

    //float alpha = texColor.a * common.material.diffuse.a * base.factorColor.a;
    
    return float4(rgb, 1.0f);
}
