#include "PreCompile.h"
#include "Stage_2_1.h"
#include "Player.h"
#include "IceBlock.h"

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

	GlobalIOManager::Load(IOType::SortMap, 4);
	DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	GlobalIOManager::Load(IOType::UnsortMap, 4);
	DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	GetMainCameraActorTransform().SetLocalPosition({ -1700, 3000, 750 });

	std::shared_ptr<Player> MainPlayer = CreateActor<Player>();
	MainPlayer->GetTransform().SetLocalPosition({ -2300, 0, -800 });
	MainPlayer->SetResponePos({ -2300, 0, -800  });

	std::shared_ptr<IceBlock> Block = CreateActor <IceBlock>();
	Block->GetTransform().SetWorldPosition({ -1383.f, 0.f, -2070.f });
	Block->SetIceBlockType(IceBlockType::Ice11);
	Block->SetIceBlockMesh(IceBlockType::Ice11);
	Block->SwitchMovable();

	return;
}