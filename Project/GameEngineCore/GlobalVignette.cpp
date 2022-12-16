#include "PreCompile.h"
#include "GlobalVignette.h"

GlobalVignette::GlobalVignette() 
{
}

GlobalVignette::~GlobalVignette() 
{
}

void GlobalVignette::EffectInit()
{
	CopyTarget = std::make_shared<GameEngineRenderTarget>();
	CopyTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);


	EffectSet = std::make_shared<GameEngineRenderUnit>();
	EffectSet->SetMaterial("Vignette");
	EffectSet->SetMesh("FullRect");
}

void GlobalVignette::Effect(std::shared_ptr<GameEngineRenderTarget> _Target)
{
	CopyTarget->Copy(_Target);

	EffectSet->ShaderResources.SetTexture("Tex", CopyTarget->GetRenderTargetTexture(0));
	_Target->Clear();
	_Target->Setting();
	_Target->Effect(EffectSet);
}
