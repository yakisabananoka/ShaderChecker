
struct VertexToPixel
{
    float4 svPos : SV_POSITION;
    float4 diffuse : COLOR0;
    float4 specular : COLOR1;
    float2 uv : TEXCOORD;
};
