struct LightData
{
    float4x4 LightViewMatrix;
    float4x4 LightProjectionMatrix;
    float LightNear;
    float LightFar;

    float4 LightColor;
    float4 AmbientLight;
    float DifLightPower;
    float SpcLightPower;
    float AmbLightPower;
    float SpcPow;

    float4 LightPos;
    float4 LightDir;
    float4 LightRevDir;

    float4 ViewLightPos;
    float4 ViewLightDir;
    float4 ViewLightRevDir;

    float4 CameraPosition;

};

cbuffer LightDatas : register(b13)
{
    int LightCount;
    LightData Lights[128];
};

float4 CalDiffuseLight(float4 _ViewNormal, LightData _LightData)
{
    _ViewNormal = normalize(_ViewNormal);
    float4 LightRevDir = normalize(_LightData.ViewLightRevDir);

    float4 DiffuseLight = max(0.0f, dot(_ViewNormal.xyz, LightRevDir.xyz));
    DiffuseLight *= _LightData.LightColor;
    DiffuseLight.w = 1.0f;

    return DiffuseLight * _LightData.DifLightPower;
}

float4 CalDiffuseLights(float4 _ViewNormal)
{
    float4 ResultLights = (float4) 0.0f;

    for (int i = 0; i < LightCount; ++i)
    {
        ResultLights += CalDiffuseLight(_ViewNormal, Lights[i]);
    }

    ResultLights.w = 1.0f;
    return ResultLights;
}

float4 CalAmbientLight(LightData _LightData)
{
    return _LightData.AmbientLight * _LightData.AmbLightPower;
}

float4 CalAmbientLight()
{
    float4 ResultLights = (float4) 0.0f;

    for (int i = 0; i < LightCount; ++i)
    {
        ResultLights += CalAmbientLight(Lights[i]);
    }

    ResultLights.w = 1.0f;
    return ResultLights;
}


float4 CalSpacularLight(float4 _ViewPosition, float4 _ViewNormal, LightData _LightData)
{
    float4 SpacularLight = (float4)0.0f;

    _ViewNormal.xyz = normalize(_ViewNormal.xyz);
    _LightData.ViewLightRevDir.xyz = normalize(_LightData.ViewLightRevDir.xyz);

    // N
    float3 Reflection = normalize(2.0f * _ViewNormal.xyz * dot(_LightData.ViewLightRevDir.xyz, _ViewNormal.xyz) - _LightData.ViewLightRevDir.xyz);
    // L
    float3 Eye = normalize(_LightData.CameraPosition.xyz - _ViewPosition.xyz);

    float Result = max(0.0f, dot(Reflection.xyz, Eye.xyz));
    SpacularLight.xyz = pow(Result, _LightData.SpcPow);
    SpacularLight.w = 1.0f;

    return SpacularLight * _LightData.SpcLightPower;
}


float4 CalSpacularLight(float4 _ViewPosition, float4 _ViewNormal)
{
    float4 ResultLights = (float4) 0.0f;

    for (int i = 0; i < LightCount; ++i)
    {
        ResultLights += CalSpacularLight(_ViewPosition, _ViewNormal, Lights[i]);
    }

    ResultLights.w = 1.0f;
    return ResultLights;
}
