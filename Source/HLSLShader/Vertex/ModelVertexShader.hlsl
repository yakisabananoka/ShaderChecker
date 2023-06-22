#include "VertexShader3DHeader.hlsli"

//�G���g���[�|�C���g
VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT ret;
    ret.svPos = float4(input.pos, 1.0f);

    ret.worldPos = mul(ret.svPos, base.localWorldMatrix);
    ret.svPos.xyz = ret.worldPos;

    ret.viewPos = mul(ret.svPos, base.viewMatrix);
    ret.svPos.xyz = ret.viewPos;

    ret.svPos = mul(ret.svPos, base.projectionMatrix);

    ret.worldNorm = normalize(mul(float4(input.norm, 0.0f), base.localWorldMatrix));
    ret.viewNorm = normalize(mul(float4(ret.worldNorm, 0.0f), base.viewMatrix));

    ret.uv = input.uv0.xy;
    ret.diffuse = input.diffuse;
    ret.specular = input.specular;

	return ret;
}