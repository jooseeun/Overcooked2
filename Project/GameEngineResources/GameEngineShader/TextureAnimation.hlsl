#include "TransformHeader.fx"

struct Input
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
    float4 NORMAL : NORMAL;
    float4 BLENDWEIGHT : BLENDWEIGHT;
    int4 BLENDINDICES : BLENDINDICES;
};

struct Output
{
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};

struct AniMat
{
    float4x4 Mat;
};

cbuffer PixelData : register(b0)
{
    float4 MulColor;
    float4 PlusColor;
    float4 Slice;

    int AlphaFlag;
    float4 AlphaColor;

}


StructuredBuffer<AniMat> ArrAniMationMatrix : register(t11);

void Skinning(inout float4 _Pos, inout float4 _Weight, inout int4 _Index, StructuredBuffer<AniMat> _ArrMatrix)
{
    float4 CalPos = (float4)0.0f;
    _Pos.w = 1.0f;
    for (int i = 0; i < 4; ++i)
    {
        AniMat Mat = _ArrMatrix[_Index[i]];
        CalPos += _Weight[i] * mul(_Pos, Mat.Mat);
    }

    _Pos = CalPos;
}

Output TextureAnimation_VS(Input _Input)
{
    Output NewOutPut = (Output)0;

    NewOutPut.POSITION = _Input.POSITION;
    Skinning(NewOutPut.POSITION, _Input.BLENDWEIGHT, _Input.BLENDINDICES, ArrAniMationMatrix);
    NewOutPut.POSITION.w = 1.0f;

    NewOutPut.POSITION = mul(NewOutPut.POSITION, WorldViewProjection);
    NewOutPut.TEXCOORD = _Input.TEXCOORD;

    return NewOutPut;
}

Texture2D DiffuseTexture : register(t0);
SamplerState LINEARWRAP : register(s0);

float4 TextureAnimation_PS(Output _Input) : SV_Target0
{    
    float4 Result = (DiffuseTexture.Sample(LINEARWRAP, _Input.TEXCOORD.xy) * MulColor) + PlusColor;
        
    
    if (AlphaFlag == 1)
    {
        
        if (Result.a <= 0.0f)
        {
            Result.r = AlphaColor.r;
            Result.g = AlphaColor.g;
            Result.b = AlphaColor.b;
            Result.a = AlphaColor.a;
        }
    


    }
    else
    {
        if (Result.a <= 0.0f)
        {
            clip(-1);
        }
    
    }
    
       return Result;
}
