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

Output Vignette_VS(Input _Input)
{
    Output NewOutPut = (Output)0;
    NewOutPut.Pos = _Input.Pos;
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

Texture2D Tex : register(t0);
SamplerState LINEARWRAP : register(s0);
float4 Vignette_PS(Output _Input) : SV_Target0
{
    float4 TexColor = Tex.Sample(LINEARWRAP, _Input.Tex.xy);
    
    float2 Resolution = { 1280, 720 };
    float2 uv = _Input.Pos.xy / Resolution.xy;
    uv *= 1.0 - uv.yx;

    float vig = uv.x * uv.y * 15.0;
    vig = pow(vig, 0.25);
    float4 fragColor = (1 - (float4)vig) * 0.5f;
    
    TexColor.xyz -= fragColor.xyz;

    if (TexColor.a == 0)
    {
        clip(-1);
    }
    if (1 <= TexColor.a)
    {
        TexColor.a = 1.0f;
    }
    return TexColor;
}
