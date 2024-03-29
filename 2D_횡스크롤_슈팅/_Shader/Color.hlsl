//========================================================
struct VertexInput
{
	float4 Position	: POSITION0;
	float4 Color	: COLOR0;
};

struct PixelInput
{
	float4 Position	: SV_POSITION;
	float4 Color	: COLOR0;
};
//========================================================

// ���ؽ� ���̴� �� �ܽ�źƮ ���� =============================
cbuffer VS_ViewProj : register(b0)
{
	matrix View;
	matrix Projection;
}

cbuffer VS_World : register(b1)
{
	matrix World;
}
//========================================================

// ���ؽ� ���̴�
PixelInput VS(VertexInput input)
{
	PixelInput output;

	output.Position = mul(input.Position, World);
	output.Position = mul(output.Position, View);
	output.Position = mul(output.Position, Projection);

	output.Color = input.Color;

	return output;
}

// �ȼ� ���̴� �� �ܽ�źƮ ���� ===============================
cbuffer PS_Color : register(b0)
{
	float4 Color;
}
//========================================================

// �ȼ� ���̴�
float4 PS(PixelInput input) : SV_TARGET
{
	return input.Color * Color;
}
