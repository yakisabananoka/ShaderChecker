
struct VertexToPixel
{
    float4 svPos : SV_POSITION;
    float3 worldPos : POSITION0;
    float3 viewPos : POSITION1;
    float4 diffuse : COLOR0;
    float4 specular : COLOR1;
    float2 uv : TEXCOORD;
};
