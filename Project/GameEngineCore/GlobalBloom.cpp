#include "PreCompile.h"
#include "GlobalBloom.h"

GlobalBloom::GlobalBloom()
{
}

GlobalBloom::~GlobalBloom()
{
}

void GlobalBloom::EffectInit()
{
	CopyTarget = std::make_shared<GameEngineRenderTarget>();
	CopyTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);

	EffectSet = std::make_shared<GameEngineRenderUnit>();
	EffectSet->SetMaterial("Bloom");
	EffectSet->SetMesh("FullRect");
	EffectSet->ShaderResources.SetConstantBufferLink("BloomOption", Option_);
}

void GlobalBloom::Effect(std::shared_ptr<GameEngineRenderTarget> _Target)
{
	CopyTarget->Copy(_Target);

	EffectSet->ShaderResources.SetTexture("Tex", CopyTarget->GetRenderTargetTexture(0));
	_Target->Clear();
	_Target->Setting();
	_Target->Effect(EffectSet);
}

