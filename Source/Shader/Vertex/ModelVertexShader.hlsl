#include "VertexShader3DHeader.hlsli"

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT ret;
    float4 svPos = float4(input.pos, 1.0f);
    
    svPos.xyz = mul(svPos, base.localWorldMatrix);
    svPos.xyz = mul(svPos, base.viewMatrix);
    svPos = mul(svPos, base.projectionMatrix);
    
    ret.svPos = svPos;
    ret.uv = input.uv0.xy;
    ret.diffuse = input.diffuse;
    ret.specular = input.specular;

	return ret;
}