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

Output Water_VS(Input _Input)
{
    Output NewOutPut = (Output)0;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.Tex = _Input.Tex * 2.5f;

    return NewOutPut;
}

Texture2D Tex : register(t0);
SamplerState LINEARWRAP : register(s0);
float4 Water_PS(Output _Input) : SV_Target0
{
    float4 TmpTex = Tex.Sample(LINEARWRAP, _Input.Tex.xy + UV.xy);
    
    float fWeight = (TmpTex.b - TmpTex.r) * sin(Random) * 0.03f;
    float2 TmpWeight = { fWeight, 0 };
    float4 Result = Tex.Sample(LINEARWRAP, _Input.Tex.xy + UV.xy + TmpWeight);
    
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
