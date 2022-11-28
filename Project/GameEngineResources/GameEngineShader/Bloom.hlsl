#include "TransformHeader.fx"
#include "RenderOption.fx"

struct Input
{
	float4 Pos : POSITION;
	float4 Tex : TEXCOORD;
};

struct Output
{
	float4 Pos : SV_POSITION;
	float4 Tex : TEXCOORD;
};

Output Bloom_VS(Input _Input)
{
	Output NewOutPut = (Output)0;
	NewOutPut.Pos = _Input.Pos;
	NewOutPut.Tex = _Input.Tex;
	return NewOutPut;
}

Texture2D Tex : register(t0);
SamplerState POINTCLAMP : register(s0);
float4 Bloom_PS(Output _Input) : SV_Target0
{
	// 밝은곳 체크
	float4 BloomColor = (float4)0;
	float4 TexColor = Tex.Sample(POINTCLAMP, _Input.Tex.xy);

	// 블러
	float2 PixelUVSize = float2(1.0f / 1280.0f, 1.0f / 720.0f);
	float2 PixelUVCenter = _Input.Tex.xy;
	float2 StartUV = PixelUVCenter + (-PixelUVSize * 14);
	float2 CurUV = StartUV;
	for (int y = 0; y < 30; ++y)
	{
		for (int x = 0; x < 30; ++x)
		{
			float4 TmpColor = Tex.Sample(POINTCLAMP, CurUV);
			float brightness = dot(TmpColor.rgb, float3(0.2126, 0.7152, 0.0722));
			if (brightness > 0.95f)
			{
				BloomColor += TmpColor;
			}
			else
			{
				BloomColor += float4(0.0, 0.0, 0.0, 1.0);
			}

			CurUV.x += PixelUVSize.x;
		}

		CurUV.x = StartUV.x;
		CurUV.y += PixelUVSize.y;
	}
	BloomColor /= 900.0f;


	float gamma = 2.2f;

	float3 result = pow(TexColor.rgb, gamma);
	float3 result2 = pow(BloomColor.rgb, gamma);
	result += result2;
	result = pow(result, (float3)(1.0f / gamma));
	TexColor = float4(result.rgb, 1.0f);


	//if (TexColor.a == 0)
	//{
	//	clip(-1);
	//}
	//if (1 <= TexColor.a)
	//{
	//	TexColor.a = 1.0f;
	//}

	return TexColor;
}
