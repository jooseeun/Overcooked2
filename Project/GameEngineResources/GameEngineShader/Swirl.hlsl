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

Output Swirl_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;
    NewOutPut.Tex = _Input.Tex /** 2.6f*/;
    
    return NewOutPut;
}

cbuffer PixelData : register(b0)
{
    float4 MulColor;
    float4 PlusColor;
    float4 Slice;

    int AlphaFlag;
    float4 AlphaColor;
    
   // float Time;
}

float swirlFun(float2 uv, float size, int arms)
{
    float angle = atan2(-uv.y + 0.5, uv.x - 0.5) + Random;
    float len = length(uv - float2(0.5, 0.5));
	
    return sin(len * size + angle * float(arms));
}

Texture2D Tex : register(t0);
SamplerState LINEARWRAP : register(s0);
float4 Swirl_PS(Output _Input) : SV_Target0
{
    //float2 PixelUVSize = float2(1.0f / 1280.0f, 1.0f / 720.0f);
    //float2 PixelUVCenter = _Input.Tex.xy;
    //float2 StartUV = PixelUVCenter + (-PixelUVSize * 2);
    
        
    float2 CurUV = _Input.Tex.xy;
    
    float4 Texture = Tex.Sample(LINEARWRAP, _Input.Tex.xy + UV.xy);
    float4 SaveTexture = Tex.Sample(LINEARWRAP, _Input.Tex.xy + UV.xy) + PlusColor;

    float swirlResult = swirlFun(CurUV, 10.0, 4) ;
   // TmpTex += float4(re, re, re, 1.0);

    float4 Result = Texture + swirlResult ;

    
    
    if (Result.r + Result.b < 1.0f)
    {
        Result.r = 0.6;
        Result.g = 0.4;
        Result.b = 0.7;
        Result.a = 1.0f;
        //clip(-1);
    }
    //if (1 <= Texture.a)
    //{
    //    Texture.a = 1.0f;
    //}
    //Texture
    return Result;

}
