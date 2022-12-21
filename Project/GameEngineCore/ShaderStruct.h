#pragma once

struct RenderOption
{
	float DeltaTime = 0.0f;
	float SumDeltaTime = 0.0f;
	int IsAnimation = 0;
	int Temp1;

	int dummy = 0;
	float4 UV = { 0, 0, 0 };
	float Random = 0.0f;
};
