// #include "myshader.hlsli"



struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;
 
};


struct Output
{
    float4 Pos : SV_POSITION;
    float4 Tex1 : TEXCOORD0;
  //  float4 Tex2 : TEXCOORD1;
};


cbuffer OverlayColorData : register(b3)
{
    float4 OverlayColor;
};

Output Overlay_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Tex1 = _Input.Tex;
   // NewOutPut.Tex2 = _Input.Tex;
    return NewOutPut;
}

// 1000
// 0100
// 2010
// 0301

// 1020
// 0103
// 0010
// 0001

//static float Gau[5][5] =
//{
//    {  }
//};


Texture2D Tex : register(t1);
SamplerState LINEARWRAP : register(s0);
float4 Overlay_PS(Output _Input) : SV_Target0
{
    float4 Result;
    
    float4 Color1 = Tex.Sample(LINEARWRAP, _Input.Tex1.xy);
    float4 Color2 = OverlayColor;
   // Color2 = OverlayColor;
    
    if (Color1.r < 0.5f)
    {
        Result.r = Color1.r * Color2.r * 2;
    }
    else
    {
        Result.r = 2 * (Color1.r + Color2.r - Color1.r * Color2.r) - 1.0f;
    }
           
    if (Color1.g < 0.5f)
    {
        Result.g = Color1.g * Color2.g * 2;
    }
    else
    {
        Result.g = 2 * (Color1.g + Color2.g - Color1.g * Color2.g) - 1.0f;
    }
            
    if (Color1.b < 0.5f)
    {
        Result.b = Color1.b * Color2.b * 2;
    }
    else
    {
        Result.b = 2 * (Color1.b + Color2.b - Color1.b * Color2.b) - 1.0f;
    }
          
      
    Result.a = Color2.a;
       
    return Result;

}
