#define VERTEX_INPUT_TYPE VERTEX_INPUT_TYPE_8FRAME
#include "VertexShader3DHeader.hlsli"

//エントリーポイント
VS_OUTPUT main(VS_INPUT input)
{
    const float4x3 lwMatrix = CalculateLocalWorldMatrix(
    input.blendIndices0,
    input.blendWeight0,
    input.blendIndices1,
    input.blendWeight1,
    localWorldMatrix);

	VS_OUTPUT ret;
    ret.svPos = float4(input.pos, 1.0f);

    ret.worldPos = mul(ret.svPos, lwMatrix);
    ret.svPos.xyz = ret.worldPos;

    ret.viewPos = mul(ret.svPos, base.viewMatrix);
    ret.svPos.xyz = ret.viewPos;

    ret.svPos = mul(ret.svPos, base.projectionMatrix);

    ret.viewNorm = normalize(mul(float4(input.norm, 0.0f), lwMatrix));
    ret.viewNorm = normalize(mul(float4(ret.viewNorm, 0.0f), base.viewMatrix));

    ret.uv = input.uv0.xy;
    ret.diffuse = input.diffuse;
    ret.specular = input.specular;

    return ret;
}
