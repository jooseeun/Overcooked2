#include "PreCompile.h"
#include "LightMap.h"

LightMap::LightMap() 
	: Renderer(nullptr)
{
}

LightMap::~LightMap() 
{
}

void LightMap::Start()
{
	{
		std::shared_ptr <GameEngineDefaultRenderer> Renderer = CreateComponent<GameEngineDefaultRenderer>();
		Renderer->SetMesh("Box");
		Renderer->SetMaterial("DeferredColor");
		Renderer->GetTransform().SetLocalScale({ 2000.0f, 50.0f, 2000.0f });

		if (true == Renderer->GetRenderUnit()->ShaderResources.IsConstantBuffer("ResultColor"))
		{
			Renderer->GetRenderUnit()->ShaderResources.SetConstantBufferNew("ResultColor", float4(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}
}

void LightMap::Update(float _DeltaTime)
{
}

