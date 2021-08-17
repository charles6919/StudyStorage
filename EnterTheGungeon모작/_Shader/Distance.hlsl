

struct VertexInput
{
	float4 Position	: POSITION0;
	float4 UV		: UV0;
};

struct PixelInput
{
	float4 Position	: SV_POSITION;
	float4 UV		: UV0;
};

// �ڹ��ؽ� ���̴��� �ܽ�źƮ ���� ============================================================================
cbuffer VS_ViewProj : register(b0) // ��register (��Ϲ�ȣ) b0 = 0��
{
	matrix View;
	matrix Projection;
}

cbuffer VS_World : register(b1)
{
	matrix World;
}
//==========================================================================================================

// �ڹ��ؽ� ���̴� (���ؽ� 1���� ������ ������ �Ѵ�.)===========================================================
PixelInput VS(VertexInput input)
{
	PixelInput output;
	output.Position = mul(input.Position, World); // �����̴������� ���ϱⰡ mul �Լ��� �����
	output.Position = mul(output.Position, View);
	output.Position = mul(output.Position, Projection);

	//output.Position = input.Position;
	output.UV = input.UV;

	return output;
}
//==========================================================================================================

// ���ȼ� ���̴��� �ܽ�źƮ ���� =============================================================================
cbuffer PS_UV : register(b0)	// ��VS�� PS�� ��ȣ�� ���� ���´�.
{
	float4 Color;
}	// ���ȼ����̴� �÷��κ��� ����

cbuffer PS_Target : register(b1)
{
	float2 TargetPos;
	float DarkSize;
	float Padding;
	// �����̴��� 16 ����Ʈ�� ������� �ܽ�ź�� ���ۻ����� �����ѵ�, 16����Ʈ�� �Ⱦ��� ��� Padding ����(�Ⱦ��� ��)��� ���������
	// ��float���� 1���� 4����Ʈ�ϱ� 4���Ǿ� 16����Ʈ
}

SamplerState	Sampler : register(s0);	// ���̹��� ������ �Ѱܹ޴°�
Texture2D		Texture : register(t0);	// ���̹��������� UV������ ���� �ؽ��� Į�� ǥ���Ŵ
//==========================================================================================================

// ���ȼ� ���̴� ============================================================================================
float4 PS(PixelInput input) : SV_TARGET
{
	float4 tColor = Texture.Sample(Sampler, input.UV);

	//if (tColor.r == 248.0f / 255.0f && tColor.g == 0.0f / 255.0f && tColor.b == 248.0f / 255.0f)	// ����Ÿ ����
	//	tColor.a == 0.0f;

	// �������� ����� �����༭ ���콺 ��ǥ ������ 0 ~ 1�� ����
	float2 target = TargetPos;
	target.x /= 1280.0f;
	target.y = 720.0f - target.y; // �����콺 ��ǥ ������
	target.y /= 720.0f;

	target.x = target.x / 9.0f * 16.0f;	// ��16:9 ������ Ÿ���� ������ �����ϰ� ����� ������ ����

	float2 UV = input.UV;
	UV.x = UV.x / 9.0f * 16.0f;

	tColor.a = 1.0f - tColor.a + distance(target, UV) * DarkSize;

	return tColor * Color;
}
//==========================================================================================================