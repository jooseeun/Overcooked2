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

Output Texture_VS(Input _Input)
{
    Output NewOutPut = (Output)0;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;
    
    return NewOutPut;
}

Texture2D DiffuseTexture : register(t0);
SamplerState LINEARWRAP : register(s0);

float4 Texture_PS(Output _Input) : SV_Target0
{
    float4 Color = DiffuseTexture.Sample(LINEARWRAP, _Input.Tex.xy);
    
    float4 PlusColor = float4(0.0f, 0.0f, 0.0f, 0.0f);
    PlusColor.a = 0.5f;
    
    //일단 알파 최대
    Color.a = 1.f;
    
    if (IsHighlight == 1)
    {
        PlusColor.r = 0.2f;
        PlusColor.g = 0.2f;
        PlusColor.b = 0.2f;
        PlusColor.a = 0.f;

    }
    else
    {
        PlusColor.r = 0.f;
        PlusColor.g = 0.f;
        PlusColor.b = 0.f;
        PlusColor.a = 0.f;
    }
    
    //if (Color.a <= 0.0f)
    //{
    //    clip(-1);
    //}
    
    return Color + PlusColor;
}
