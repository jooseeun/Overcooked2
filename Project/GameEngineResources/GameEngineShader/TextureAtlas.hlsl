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
};

cbuffer AtlasData : register(b1)
{
    float2 TextureFramePos;
    float2 TextureFrameSize;
    float4 PivotPos;
};


Output TextureAtlas_VS(Input _Input)
{
    Output NewOutPut = (Output)0;
    _Input.Pos += PivotPos;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;
    
    NewOutPut.Tex.x = (_Input.Tex.x * TextureFrameSize.x) + TextureFramePos.x;
    NewOutPut.Tex.y = (_Input.Tex.y * TextureFrameSize.y) + TextureFramePos.y;
    
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
float4 TextureAtlas_PS(Output _Input) : SV_Target0
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

struct InstAtlasData
{
    float2 TextureFramePos;
    float2 TextureFrameSize;
    float4 PivotPos;
};

StructuredBuffer<InstTransformData> Inst_TransformData : register(t12);
StructuredBuffer<InstAtlasData> Inst_AtlasData : register(t13);

Output TextureAtlas_VSINST(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Pos = mul(_Input.Pos, Inst_TransformData[_Input.Index].WorldViewProjection);

    NewOutPut.Tex.x = (_Input.Tex.x * Inst_AtlasData[_Input.Index].TextureFrameSize.x) + Inst_AtlasData[_Input.Index].TextureFramePos.x;
    NewOutPut.Tex.y = (_Input.Tex.y * Inst_AtlasData[_Input.Index].TextureFrameSize.y) + Inst_AtlasData[_Input.Index].TextureFramePos.y;

    return NewOutPut;
}
