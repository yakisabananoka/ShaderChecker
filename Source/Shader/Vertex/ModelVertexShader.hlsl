#include "VertexShader3DHeader.hlsli"

//エントリーポイント
VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT ret;

    ret.svPos = float4(input.pos, 1.0f);
    
    ret.svPos.xyz = mul(ret.svPos, base.localWorldMatrix);
    ret.svPos.xyz = mul(ret.svPos, base.viewMatrix);
    ret.svPos = mul(ret.svPos, base.projectionMatrix);

    ret.uv = input.uv0.xy;
    ret.diffuse = input.diffuse;
    ret.specular = input.specular;

	return ret;
}