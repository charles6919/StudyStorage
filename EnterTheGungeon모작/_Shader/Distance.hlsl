

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

// ★버텍스 셰이더용 콘스탄트 버퍼 ============================================================================
cbuffer VS_ViewProj : register(b0) // ▶register (등록번호) b0 = 0번
{
	matrix View;
	matrix Projection;
}

cbuffer VS_World : register(b1)
{
	matrix World;
}
//==========================================================================================================

// ★버텍스 쉐이더 (버텍스 1개의 정보를 가지고 한다.)===========================================================
PixelInput VS(VertexInput input)
{
	PixelInput output;
	output.Position = mul(input.Position, World); // ▶쉐이더에서는 곱하기가 mul 함수로 써야함
	output.Position = mul(output.Position, View);
	output.Position = mul(output.Position, Projection);

	//output.Position = input.Position;
	output.UV = input.UV;

	return output;
}
//==========================================================================================================

// ★픽셀 셰이더용 콘스탄트 버퍼 =============================================================================
cbuffer PS_UV : register(b0)	// ▶VS랑 PS는 번호를 각각 갖는다.
{
	float4 Color;
}	// ▶픽셀쉐이더 컬러부분을 만듬

cbuffer PS_Target : register(b1)
{
	float2 TargetPos;
	float DarkSize;
	float Padding;
	// ▶쉐이더는 16 바이트씩 맞춰줘야 콘스탄스 버퍼생성이 가능한데, 16바이트를 안쓰는 경우 Padding 변수(안쓰는 값)라고 맞춰줘야함
	// ▶float값이 1개당 4바이트니깐 4개되야 16바이트
}

SamplerState	Sampler : register(s0);	// ▶이미지 정보를 넘겨받는곳
Texture2D		Texture : register(t0);	// ▶이미지정보와 UV정보를 통해 텍스쳐 칼라를 표출시킴
//==========================================================================================================

// ★픽셀 쉐이더 ============================================================================================
float4 PS(PixelInput input) : SV_TARGET
{
	float4 tColor = Texture.Sample(Sampler, input.UV);

	//if (tColor.r == 248.0f / 255.0f && tColor.g == 0.0f / 255.0f && tColor.b == 248.0f / 255.0f)	// 마젠타 색상값
	//	tColor.a == 0.0f;

	// ▶윈도우 사이즈를 나눠줘서 마우스 좌표 기준을 0 ~ 1로 만듬
	float2 target = TargetPos;
	target.x /= 1280.0f;
	target.y = 720.0f - target.y; // ▶마우스 좌표 뒤집기
	target.y /= 720.0f;

	target.x = target.x / 9.0f * 16.0f;	// ▶16:9 비율의 타원을 비율을 동등하게 만들어 원으로 변형

	float2 UV = input.UV;
	UV.x = UV.x / 9.0f * 16.0f;

	tColor.a = 1.0f - tColor.a + distance(target, UV) * DarkSize;

	return tColor * Color;
}
//==========================================================================================================