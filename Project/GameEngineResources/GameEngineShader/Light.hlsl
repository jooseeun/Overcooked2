#include "TransformHeader.fx"
#include "LightHeader.fx"

struct Input
{
    float4 Pos : POSITION;
    float4 Normal : NORMAL0;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 ViewPos : POSITION;
    float4 Normal : NORMAL0;
};

Output Light_VS(Input _Input)
{
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

float4 Light_PS(Output _Input) : SV_Target0
{
    LightData Data;
    Data.LightDir = float4(1.0f, 0.0f, 0.0f, 0.0f);
    Data.LightRevDir = float4(-1.0f, 0.0f, 0.0f, 0.0f);
    Data.LightRevDir = mul(Data.LightRevDir, WorldView);

    float4 DiffuseLight = CalDiffuseLights(_Input.Normal);
    float4 SpacularLight = CalSpacularLight(_Input.ViewPos, _Input.Normal);
    float4 AmbientLight = CalAmbientLight();


    // Color
    float4 LightEffectResult = Color * (DiffuseLight + SpacularLight + AmbientLight);
    LightEffectResult.w = 1.0f;

    return LightEffectResult;
}
