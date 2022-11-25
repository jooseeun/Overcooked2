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

Output JBMWater_VS(Input _Input)
{
    Output NewOutPut = (Output)0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;
    return NewOutPut;
}

Texture2D Tex : register(t0);
SamplerState LINEARWRAP : register(s0);
float4 JBMWater_PS(Output _Input) : SV_Target0
{
    float4 Result = Tex.Sample(LINEARWRAP, _Input.Tex.xy + UV.xy);

    if (Result.a == 0)
    {
        clip(-1);
    }
    if (1 <= Result.a)
    {
        Result.a = 1.0f;
    }

    return Result;
}
