#include "LightHeader.fx"
#include "TransformHeader.fx"
#include "RenderOption.fx"

struct Input
{
    float4 POSITION : POSITION;
    float4 WEIGHT : BLENDWEIGHT0; // 내가 곱해져야할 뼈에게 얼마나 영향을 받느냐에 대한 정보.
    int4 INDICES : BLENDINDICES0; // 내가 곱해져야할 뼈의 인덱스 정보
};

struct Output
{
    float4 POSITION : SV_POSITION;
    float4 VPPOSITION : TEXCOORD;
};

Output Shadow_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    
    NewOutPut.POSITION = mul(_Input.POSITION, WorldViewProjection);
    NewOutPut.VPPOSITION = mul(_Input.POSITION, WorldViewProjection);
    
    return NewOutPut;
}

float4 Shadow_PS(Output _Input) : SV_Target0
{
    return float4(_Input.VPPOSITION.z / _Input.VPPOSITION.w, 0.0f, 0.0f, 1.0f);
}