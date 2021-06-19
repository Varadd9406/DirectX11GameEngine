cbuffer Cbuf
{
	matrix transform;
};
float4 main(float3 pos : Position): SV_Position
{
	return mul(float4(pos.x, pos.y, pos.z, 1.0f), transform);
}