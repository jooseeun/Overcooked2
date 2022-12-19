#include "PreCompile.h"
#include "GlobalBloomActor.h"

GlobalBloomActor::GlobalBloomActor() 
{
}

GlobalBloomActor::~GlobalBloomActor() 
{
}

void GlobalBloomActor::Start()
{
	BloomEffectRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	BloomEffectRenderer_->SetOrder(99);
	BloomEffectRenderer_->SetRenderingOrder(99);
	BloomEffectRenderer_->SetMaterial("AddBlendAlpha");
	BloomEffectRenderer_->SetTexture("BloomEffect.png");
	BloomEffectRenderer_->GetShaderResources().SetConstantBufferLink("PixelData", &PixelData_, sizeof(PixelData));
}

void GlobalBloomActor::Update(float _Delta)
{
	//GetTransform().SetAddWorldRotation(float4(0, 100, 0) * _Delta);
	//GetTransform().SetWorldRotation(float4::GetDegree3D(GetTransform().GetWorldPosition(), GetLevel()->GetMainCameraActorTransform().GetWorldPosition()));
}

