#include "PreCompile.h"
#include "Stage_2_1.h"
#include "Player.h"

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

	CreateActor<LevelActor>()->SetLevelMesh("1_4.FBX");

	GlobalIOManager::Load(IOType::SortMap, 3);
	DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	GlobalIOManager::Load(IOType::UnsortMap, 3);
	DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);
	GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	GetMainCameraActorTransform().SetLocalPosition({ -1173  , 3300   , 2500 });

	std::shared_ptr<Player> MainPlayer = CreateActor<Player>();
	MainPlayer->GetTransform().SetLocalPosition({ -1000, 1000, 1000 });
	return;
}