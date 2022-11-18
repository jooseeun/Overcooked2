#include "TransformHeader.fx"
#include "RenderOption.fx"

struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;
    
    // 인스턴싱 데이터
    uint Index : ROWINDEX;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 PosLocal : POSITION;
    float4 Tex : TEXCOORD;
    float4 MaskTex : TEXCOORD1;
};

cbuffer AtlasData : register(b1)
{
    float2 TextureFramePos;
    float2 TextureFrameSize;
    float4 PivotPos;
};

cbuffer UIData : register(b2)
{
    int UIMode; // 0 : 기본, 1 : MaskMode , 2: TransitionMode
    
    float4 DownDelta;
};


Output UI_VS(Input _Input)
{
    Output NewOutPut = (Output)0;
    _Input.Pos += PivotPos;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;
    
    NewOutPut.Tex.x = (_Input.Tex.x * TextureFrameSize.x) + TextureFramePos.x;
    NewOutPut.Tex.y = (_Input.Tex.y * TextureFrameSize.y) + TextureFramePos.y;
    
    //마스크용
    NewOutPut.MaskTex = _Input.Tex;
    
    //내가 이동시키는 좌표
    if (DownDelta.x > 0.5)
    {
        NewOutPut.Tex.y -= DownDelta.y;

    }
    
    //Transition용
    if(UIMode == 2)
    {
        Output NewOutPut = (Output) 0;
        NewOutPut.Pos = _Input.Pos;
        NewOutPut.Tex = _Input.Tex;
    }
    return NewOutPut;
}

cbuffer PixelData : register(b0)
{
    float4 MulColor;
    float4 PlusColor;
    float4 Slice;
}

Texture2D Tex : register(t0);
Texture2D Tex2 : register(t1);
SamplerState LINEARWRAP : register(s0);
float4 UI_PS(Output _Input) : SV_Target0
{
    if (UIMode == 0)
    {
        if (_Input.Tex.x < Slice.x)
        {
            clip(-1);
        }
    
        if (_Input.Tex.y < Slice.y)
        {
            clip(-1);
        }
    
        float4 TexColor = Tex.Sample(LINEARWRAP, _Input.Tex.xy);
        if (TexColor.a == 0)
        {
            clip(-1);
        }
    
        float4 Result = (Tex.Sample(LINEARWRAP, _Input.Tex.xy) * MulColor) + PlusColor;
    
        if (1 <= Result.a)
        {
            Result.a = 1.0f;

        }
    
        return Result;
    }
    else if (UIMode == 1)
    {
    
        if (_Input.Tex.x < Slice.x)
        {
            clip(-1);
        }
    
        if (_Input.Tex.y < Slice.y)
        {
            clip(-1);
        }
    
        float4 TexColor = Tex.Sample(LINEARWRAP, _Input.Tex.xy);
        float4 TexColor2 = Tex2.Sample(LINEARWRAP, _Input.MaskTex.xy);
        //if(TexColor2.a == 0)
        //{
        //    clip(-1);
        //}
        if (TexColor.a == 0)
        {
            clip(-1);
        }
    
        float4 Result = ((Tex.Sample(LINEARWRAP, _Input.Tex.xy) * MulColor) + PlusColor)*TexColor2.a;
        
    
        if (1 <= Result.a)
        {
            Result.a = 1.0f;

        }
        //if (0.1f <= Result.a)
        //{
        //    Result.a = -100.f;

        //}
        return Result;
    }
    else if (UIMode == 2)
    {
        float4 Result = (0, 0, 0, 0);
        float4 TexColor = Tex.Sample(LINEARWRAP, _Input.Tex.xy);
        if(TexColor.a <= 0.1)
        {
            Result.a = -10;
            return Result;
        }
        return Result;
    }
    if (UIMode == 3) //Loading 바 (Left To Right)
    {
        if (_Input.Tex.x > Slice.x)
        {
            clip(-1);
        }
    
        if (_Input.Tex.y < Slice.y)
        {
            clip(-1);
        }
    
        float4 TexColor = Tex.Sample(LINEARWRAP, _Input.Tex.xy);
        if (TexColor.a == 0)
        {
            clip(-1);
        }
    
        float4 Result = (Tex.Sample(LINEARWRAP, _Input.Tex.xy) * MulColor) + PlusColor;
    
        if (1 <= Result.a)
        {
            Result.a = 1.0f;

        }
    
        return Result;
    }
    return (Tex.Sample(LINEARWRAP, _Input.Tex.xy) * MulColor) + PlusColor;
    
    
}

Output UI_VSINST(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Pos = mul(_Input.Pos, AllInstancingTransformData[_Input.Index].WorldViewProjection);
    NewOutPut.Tex = _Input.Tex;
    return NewOutPut;
}
