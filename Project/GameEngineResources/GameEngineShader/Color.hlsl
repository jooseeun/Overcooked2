#include "TransformHeader.fx"
#include "LightHeader.fx"

struct Input
{
    float4 Pos : POSITION;
    float4 Normal : NORMAL;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 ViewPos : POSITION;
    float4 Normal : NORMAL;
};

Output Color_VS(Input _Input)
{
    // 쉐이더의 경우에는 대부분의 상황에서 형변환이 가능하다.
    Output NewOutPut = (Output)0;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.ViewPos = mul(_Input.Pos, WorldView);
    
    _Input.Normal.w = 0.0f;
    NewOutPut.Normal = mul(_Input.Normal, WorldView);
    NewOutPut.Normal.w = 0.0f;
    
    return NewOutPut;
}

cbuffer ResultColor : register(b8)
{
    float4 Color;
}

float4 Color_PS(Output _Input) : SV_Target0
{
    float4 DiffuseLight = CalDiffuseLights(_Input.Normal);
    
    float4 Result = Color * DiffuseLight;
    
    return Result;
}
