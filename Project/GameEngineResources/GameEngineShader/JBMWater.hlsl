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

Output JBMWater_VS(Input _Input)
{
    Output NewOutPut = (Output)0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;
    return NewOutPut;
}

float Random(float2 p)
{
    return frac(sin(dot(p, float2(12.9898, 78.233))) * 43758.5453123);
}

Texture2D Tex : register(t0);
SamplerState LINEARWRAP : register(s0);
float4 JBMWater_PS(Output _Input) : SV_Target0
{
    float4 Result = Tex.Sample(LINEARWRAP, _Input.Tex.xy + UV.xy);
  //  float fWeight = Result.b * 0.5f;

    if (Result.a == 0)
    {
        clip(-1);
    }
    if (1 <= Result.a)
    {
        Result.a = 1.0f;
    }

    return Result;
}

///////////////////////////

//PS_OUTPUT_SINGLE FX_Distortion(VS_OUTPUT_TEX input)
//{
//    PS_OUTPUT_SINGLE output = (PS_OUTPUT_SINGLE)0;
//
//    float4 vFX_tex = g_EffectTex1.Sample(g_LinearSmp, input.vUV);
//    float4	vColor = (float4)0.f;
//    float fWeight = vFX_tex.r * 0.5f;
//
//    if (g_iAnimation2DEnable == 0)
//    {
//        vColor = g_DiffuseTex.Sample(g_LinearSmp, input.vUV + fWeight);
//    }
//    else
//    {
//        if (g_iAnim2DType == AT_ATLAS)
//            vColor = g_DiffuseTex.Sample(g_LinearSmp, input.vUV + fWeight);
//        else
//            vColor = g_ArrayTex.Sample(g_LinearSmp, float3(input.vUV + fWeight, g_iAnim2DFrame));
//    }
//
//    output.vColor = vColor;
//    return output;
//}
