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
	BloomEffectRenderer_->SetTexture("BloomEffect.png");
	BloomEffectRenderer_->GetTransform().SetWorldScale(float4::ONE * 100);
}

void GlobalBloomActor::Update(float _Delta)
{
}

