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

#define PI 3.14159265359f

float swirlFun(float2 uv, float size, int arms)
{
    float angle = atan2(-uv.y + 0.5, uv.x - 0.5) + Random;
    float len = length(uv - float2(0.5, 0.5));
	
    return sin(len * size + angle * float(arms));
}

float2 rotateUV(float2 uv, float degrees)
{
    const float Deg2Rad = (PI * 2.0) / 360.0; //1도의 라디안값을 구한다 
    float rotationRadians = degrees * Deg2Rad; //원하는 각도(디그리)의 라디안 값을 구한다 
    float s = sin(rotationRadians);
    float c = cos(rotationRadians);
    float2x2 rotationMatrix = float2x2(c, -s, s, c); //회전 2차원 행렬을 만든다 
    uv.xy -= 0.5; //중심축을 이동시켜 가운데로 만들고 
    uv.xy = mul(rotationMatrix, uv.xy); //회전한 다음에 
    uv.xy += 0.5; //다시 중심축 이동시켜 제자리로 만든다 
    return uv;
}

Texture2D Tex : register(t0);
SamplerState LINEARWRAP : register(s0);
float4 Swirl_PS(Output _Input) : SV_Target0
{
    //float2 PixelUVSize = float2(1.0f / 1280.0f, 1.0f / 720.0f);
    //float2 PixelUVCenter = _Input.Tex.xy;
    //float2 StartUV = PixelUVCenter + (-PixelUVSize * 2);
    
        
    float2 CurUV = _Input.Tex.xy;
    
    

  //  float4 Texture = Tex.Sample(LINEARWRAP, _Input.Tex.xy + UV.xy);
    float4 SaveTexture = Tex.Sample(LINEARWRAP, _Input.Tex.xy + UV.xy) + PlusColor;

    float2 swirlResult = rotateUV(CurUV, Random);
    SaveTexture.xy += swirlResult.xy;
    //SaveTexture.x = swirlResult.x;
    //SaveTexture.y = swirlResult.y;
    
   // TmpTex += float4(re, re, re, 1.0);

  //  float4 Result = Texture + swirlResult ;


    //if (1 <= Texture.a)
    //{
    //    Texture.a = 1.0f;
    //}
    //Texture
    return SaveTexture;

}
