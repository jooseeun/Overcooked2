#include "TransformHeader.fx"
#include "LightHeader.fx"
#include "DeferredHeader.fx"

struct Input
{
    float4 Pos : POSITION;
    float4 Normal : NORMAL;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 ViewPos : POSITION;
    float4 ViewNormal : NORMAL;
};

Output DeferredColor_VS(Input _Input)
{
    Output NewOutPut = (Output)0;

    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);

    NewOutPut.ViewPos = mul(_Input.Pos, WorldView);

    _Input.Normal.w = 0.0f;
    NewOutPut.ViewNormal = normalize(mul(_Input.Normal, WorldView));
    NewOutPut.ViewNormal.w = 0.0f;
    
    return NewOutPut;
}

cbuffer ResultColor : register(b8)
{
    float4 Color;
}

DeferredOutPut DeferredColor_PS(Output _Input) : SV_Target0
{
    DeferredOutPut OutPut;

    OutPut.Dif = Color;
    OutPut.Pos = _Input.ViewPos;
    OutPut.Nor = _Input.ViewNormal;
    OutPut.Nor.w = 1.0f;

    return OutPut;
}
