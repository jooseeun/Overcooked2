#include "LightHeader.fx"

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

Output CalDeferredLight_VS(Input _Input)
{
    Output NewOutPut = (Output)0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;
    return NewOutPut;
}

Texture2D PositionTex : register(t0);
Texture2D NormalTex : register(t1);
SamplerState POINTWRAP : register(s0);

struct LightOutPut
{
    float4 DifLight : SV_Target0;
    float4 SpcLight : SV_Target1;
    float4 AmbLight : SV_Target2;
};

LightOutPut CalDeferredLight_PS(Output _Input)
{
    float4 Position = PositionTex.Sample(POINTWRAP, _Input.Tex.xy);
    float4 Normal = NormalTex.Sample(POINTWRAP, _Input.Tex.xy);

    if (Position.a <= 0.0f)
    {
        clip(-1);
    }

    Normal.w = 0.0f;

    LightOutPut Out = (LightOutPut)0.0f;

    Out.DifLight = CalDiffuseLights(Normal);
    Out.SpcLight = CalSpacularLight(Position, Normal);
    Out.AmbLight = CalAmbientLight();

    return Out;
}