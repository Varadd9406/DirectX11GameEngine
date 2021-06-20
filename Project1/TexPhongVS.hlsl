cbuffer Cbuf
{
    matrix modelView;
    matrix modelViewProj;
};

struct VSout
{
    float3 worldPos : Position;
    float3 normal : Normal;
    float2 tc : Texcoord;
    float4 pos : SV_Position;
};

VSout main(float3 pos : POSITION, float3 n : Normal,float2 tc : Texcoord)
{
    VSout vso;
    vso.worldPos = (float3) mul(float4(pos, 1.0f), modelView);
    vso.normal = mul(n, (float3x3) modelView);
    vso.pos = mul(float4(pos, 1.0f), modelViewProj);
    vso.tc = tc;
    return vso;
}