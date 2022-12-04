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
    float4 PosLocal : POSITION;
    float4 Tex : TEXCOORD;
};

Output Glass_VS(Input _Input)
{
    Output NewOutPut = (Output)0;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;
    return NewOutPut;
}

cbuffer PixelData : register(b0)
{
    float4 MulColor;
    float4 PlusColor;
    float4 Slice;

    int AlphaFlag;
    float4 AlphaColor;
}

Texture2D DiffuseTexture : register(t0);
SamplerState LINEARWRAP : register(s0);

float4 Glass_PS(Output _Input) : SV_Target0
{
    float4 Result = (DiffuseTexture.Sample(LINEARWRAP, _Input.Tex.xy + UV.xy) * MulColor) + PlusColor;
    Result.a = 0.2f;

    return Result;
}
