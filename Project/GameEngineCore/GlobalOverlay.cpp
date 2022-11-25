#include "PreCompile.h"
#include "GlobalOverlay.h"

GlobalOverlay::GlobalOverlay() 
	:
	CopyTarget(nullptr),
	EffectSet(),

	OverlayColorData_{}
{
}

GlobalOverlay::~GlobalOverlay() 
{
}

void GlobalOverlay::EffectInit()
{
	CopyTarget = std::make_shared<GameEngineRenderTarget>();
	CopyTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);

	EffectSet.SetMaterial("Overlay");
	EffectSet.SetMesh("FullRect");

	OverlayColorData_.OverlayColor = { 0.586f, 0.617f, 0.672f, 1.0f };

	EffectSet.ShaderResources.SetConstantBufferLink("OverlayColorData", OverlayColorData_);

}

void GlobalOverlay::Effect(std::shared_ptr<GameEngineRenderTarget> _Target)
{
	CopyTarget->Copy(_Target);

	EffectSet.ShaderResources.SetTexture("Tex", CopyTarget->GetRenderTargetTexture(0));
	OverlayColorData_;
	_Target->Clear();
	_Target->Setting();
	_Target->Effect(EffectSet);

}

