#include "PreCompile.h"
#include "RendererTestLevel.h"
#include "GlobalBloomActor.h"

RendererTestLevel::RendererTestLevel() 
{
}

RendererTestLevel::~RendererTestLevel() 
{
}

void RendererTestLevel::Start()
{
}

void RendererTestLevel::Update(float _DeltaTime)
{
}

void RendererTestLevel::End()
{
}

void RendererTestLevel::LevelStartEvent()
{
	if (IsLevelFirst_ == false)
	{
		return;
	}

	IsLevelFirst_ = false;
	std::shared_ptr<LevelActor> LevelActor_ = CreateActor<LevelActor>();
	LevelActor_->SetLevelMesh("1_1.FBX");
	LevelActor_->GetRenderer()->SetSubMaterial(6, "TextureAlpha");
	LevelActor_->GetRenderer()->SetSubMaterial(31, "Glass");
	LevelActor_->GetRenderer()->SetSubMaterial(32, "AddBlendAlpha");
	LevelActor_->GetRenderer()->SetSubMaterial(33, "AddBlendAlpha");
	LevelActor_->GetRenderer()->SetSubMaterial(16, "TextureAlpha");

	//GlobalIOManager::Load(IOType::SortMap, 0);
	//DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), GameEngineCore::FindLevel("1-1"));

	GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	GetMainCameraActorTransform().SetLocalPosition({ -1400, 2200, 1600 });

	std::shared_ptr<GlobalBloomActor> BloomActor = CreateActor<GlobalBloomActor>();
	BloomActor->GetTransform().SetLocalPosition({ -1400, 500, 200 });
	BloomActor->GetTransform().SetWorldScale(float4::ONE * 500);
}
