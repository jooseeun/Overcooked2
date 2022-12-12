#include "PreCompile.h"
#include "Stage_2_1.h"
#include "Player.h"
#include "IceBlock.h"
#include "Cannon.h"
#include "Button.h"

#include "PortalCollision.h"

Stage_2_1::Stage_2_1()
{
}

Stage_2_1::~Stage_2_1()
{
}

void Stage_2_1::PlayLevelStart()
{
}

void Stage_2_1::PlayLevelUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDownKey("SubTest"))
	{
		SubsetDebugIndex_++;
		LevelActor_->GetRenderer()->SetSubMaterial(SubsetDebugIndex_, "Glass");

		GameEngineDebug::OutPutString(std::to_string(SubsetDebugIndex_));
	}

	WaterRenderOption1_.UV.y += _DeltaTime * 0.25f;
	WaterRenderOption2_.UV.y += _DeltaTime * 0.25f;
}

void Stage_2_1::End()
{
}

void Stage_2_1::PlayLevelStartEvent()
{
	if (IsLevelFirst_ == false)
	{
		return;
	}

	IsLevelFirst_ = false;

	LevelActor_ = CreateActor<LevelActor>();
	LevelActor_->SetLevelMesh("2_1.FBX");

	WaterActor_ = CreateActor<GameEngineActor>();
	WaterActor_->GetTransform().SetWorldScale({ 2000, 3000, 1 });
	WaterActor_->GetTransform().SetWorldPosition({-1500.f, -50.f, -1200.f});
	WaterActor_->GetTransform().SetWorldRotation({ 90.f, 0.f, 0.f });

	{
		std::shared_ptr<GameEngineTextureRenderer> Water = WaterActor_->CreateComponent<GameEngineTextureRenderer>();
		Water->SetMaterial("JBMWater");
		Water->SetTexture("Icy_Water.png");
		Water->GetShaderResources().SetConstantBufferLink("RENDEROPTION", &WaterRenderOption1_, sizeof(RenderOption));
	}

	{
		std::shared_ptr<GameEngineTextureRenderer> Water = WaterActor_->CreateComponent<GameEngineTextureRenderer>();
		Water->SetMaterial("JBMWater");
		Water->SetTexture("water2.png");
		Water->GetShaderResources().SetConstantBufferLink("RENDEROPTION", &WaterRenderOption2_, sizeof(RenderOption));
	}

	GlobalIOManager::Load(IOType::SortMap, 4);
	DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	GlobalIOManager::Load(IOType::UnsortMap, 4);
	DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	GetMainCameraActorTransform().SetLocalPosition({ -1700, 3000, 750 });

	std::shared_ptr<Player> MainPlayer = CreateActor<Player>();
	MainPlayer->GetTransform().SetLocalPosition({ -2300, 0, -800 });
	MainPlayer->SetResponePos({ -2300, 0, -800 });

	std::shared_ptr<IceBlock> Block = CreateActor <IceBlock>();
	Block->GetTransform().SetWorldPosition({ -1383.f, 0.f, -2070.f });
	Block->SetIceBlockType(IceBlockType::Ice11);
	Block->SetIceBlockMesh(IceBlockType::Ice11);
	Block->SwitchMovable();

	std::shared_ptr<PortalCollision> Puple1 = CreateActor<PortalCollision>();
	Puple1->SetPotalType(MapObjType::Portal_Blue);
	Puple1->GetTransform().SetWorldPosition({ -591.00,260.00,-1402.00 });

	std::shared_ptr<PortalCollision> Puple2 = CreateActor<PortalCollision>();
	Puple2->SetPotalType(MapObjType::Portal_Blue);
	Puple2->GetTransform().SetWorldPosition({ -2688.00,50.00,-1021.00 });

	Puple1->SetNextPotal(Puple2);
	Puple1->SetNextPos({ -2688.00,50.00,-1021.00 });

	Puple2->SetNextPotal(Puple1);
	Puple2->SetNextPos({ -591.00,260.00,-1402.00 });

	std::shared_ptr<Cannon> CannonObj = CreateActor<Cannon>();
	CannonObj->GetTransform().SetWorldPosition({-606.f, 0.f, -1111.f});

	std::shared_ptr<Button> ButtonObj = CreateActor<Button>();
	ButtonObj->GetTransform().SetWorldPosition({ -606.f, 0.f, -989.f });

	return;
}