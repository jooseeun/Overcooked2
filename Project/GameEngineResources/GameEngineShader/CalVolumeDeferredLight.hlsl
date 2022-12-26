#include "TransformHeader.fx"
#include "LightHeader.fx"

// SV_POSITION �ø�ƽ
// �׷���ī�忡�� �̳༮�� �̷� �η��ϱ� �ϰ� �ڵ����� ó���ϴ� �༮�� ������ �ϰ�.


struct Input
{
    float4 Pos : POSITION;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 UvPos : POSITION;
};


// �׷���ī�忡�� �̷����°�.
Output CalDeferredLight_VS(Input _Input)
{
    Output NewOutPut = (Output)0;
    
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.UvPos = NewOutPut.Pos;
    return NewOutPut;
}

// �𷺼� ����Ʈ���� ������ �ʿ�����ϴ�.
// ����Ʈ ����Ʈ�� ��������Ʈ���� 

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
    //                    -1        1               
    float2 UV = float2(_Input.UvPos.x / _Input.UvPos.w, _Input.UvPos.y / _Input.UvPos.w);
    
    //             0~1
    UV = float2(UV.x * 0.5f + 0.5f, UV.y * -0.5f + 0.5f);
    
    float4 Position = PositionTex.Sample(POINTWRAP, UV);
    float4 Normal = NormalTex.Sample(POINTWRAP, UV);
    
    if (Position.a <= 0.0f)
    {
        clip(-1);
    }
    
    Normal.w = 0.0f;
    
    LightOutPut Out = (LightOutPut) 0.0f;
    
    Out.DifLight = CalDiffuseLights(Position, Normal);
    Out.SpcLight = CalSpacularLight(Position, Normal);
    Out.AmbLight = CalAmbientLight();
    
    int Count = 0;
    
        if (Out.DifLight.x > 0.0f)
        {
            // ī�޶��� view���� ���� ViewPosition
            // ���� view ī�޶��� view������ �Ѵ�.
            // �Ѵ� ������ view������ �ֽ��ϴ�.
            // ������ view�� ������� �������.
            // ���� -> �� -> �������� -> ����Ʈ(SV_POSTION)
            
            // Position ���� * ī�޶�view
            
            // ViewPositionī�޶� ������ �ֱ� ������ ī�޶��� ������� ���;� �Ѵ�.
            float4 WorldPosition = mul(float4(Position.xyz, 1.0f), Lights[0].CameraViewInverseMatrix);
            
            // WorldPosition ī�޶��� ������ => ���� �������� ����鿩�� �մϴ�.
            float4 LightPos = mul(WorldPosition, Lights[0].LightViewProjectionMatrix);
            
            float fDepth = LightPos.z / LightPos.w; // 0 ~ 1 
            float fUvX = LightPos.x / LightPos.w; // -1 1
            float fUvY = LightPos.y / LightPos.w; // -1 1
            
            // fUvX -1 1
            // fUvY -1 1
            // ShaodwPos
            
            // �׸��ڸ� �������� ���� uv��
            float2 ShadowUv = float2(fUvX * 0.5f + 0.5f, fUvY * -0.5f + 0.5f);
            
            // UV���� �ܺζ�� ���� �������� �ʴ´�.
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