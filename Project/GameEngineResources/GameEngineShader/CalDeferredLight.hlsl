#include "LightHeader.fx"

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

Output CalDeferredLight_VS(Input _Input)
{
    Output NewOutPut = (Output)0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;
    return NewOutPut;
}

Texture2D PositionTex : register(t0);
Texture2D NormalTex : register(t1);
Texture2D ShadowTex : register(t2);
SamplerState POINTWRAP : register(s0);
SamplerState LINEARWRAP : register(s1);

struct LightOutPut
{
    float4 DifLight : SV_Target0;
    float4 SpcLight : SV_Target1;
    float4 AmbLight : SV_Target2;
};

LightOutPut CalDeferredLight_PS(Output _Input)
{
    float4 Position = PositionTex.Sample(POINTWRAP, _Input.Tex.xy);
    float4 Normal = NormalTex.Sample(POINTWRAP, _Input.Tex.xy);

    if (Position.a <= 0.0f)
    {
        clip(-1);
    }

    Normal.w = 0.0f;

    LightOutPut Out = (LightOutPut)0.0f;

    Out.DifLight = CalDiffuseLights(Position, Normal);
    Out.SpcLight = CalSpacularLight(Position, Normal);
    Out.AmbLight = CalAmbientLight();

    int Count = 0;

    if (Out.DifLight.x > 0.0f)
    {
        float4 WorldPosition = mul(float4(Position.xyz, 1.0f), Lights[0].CameraViewInverseMatrix);

        float4 LightPos = mul(WorldPosition, Lights[0].LightViewProjectionMatrix);

        float fDepth = LightPos.z / LightPos.w; // 0 ~ 1 
        float fUvX = LightPos.x / LightPos.w; // -1 1
        float fUvY = LightPos.y / LightPos.w; // -1 1

        // 그림자를 가져오기 위한 uv값
        float2 ShadowUv = float2(fUvX * 0.5f + 0.5f, fUvY * -0.5f + 0.5f);

        // UV공간 외부라면 굳이 가져오지 않는다.
        if (
            0.001f < ShadowUv.x && 0.999f > ShadowUv.x &&
            0.001f < ShadowUv.y && 0.999f > ShadowUv.y
            )
        {
            // Texture2DArray.Sample

            float fShadowDepth = ShadowTex.Sample(LINEARWRAP, float2(ShadowUv.x, ShadowUv.y)).r;

            if (0.0f < fShadowDepth && fDepth > fShadowDepth + 0.001f)
            {
                Out.DifLight = 0.01f;
                Out.SpcLight = 0.01f;
            }
        }
    }

    return Out;
}