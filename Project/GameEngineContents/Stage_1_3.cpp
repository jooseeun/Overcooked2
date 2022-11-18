#include "PreCompile.h"
#include "Stage_1_3.h"
#include "Player.h"

Stage_1_3::Stage_1_3()
{
}

Stage_1_3::~Stage_1_3()
{
}

void Stage_1_3::PlayLevelStart()
{
	//CreateActor<LevelActor>()->SetLevelMesh("1_3.FBX");

	//GlobalIOManager::Load(IOType::SortMap, 2);
	//DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	//GlobalIOManager::Load(IOType::UnsortMap, 2);
	//DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);
	//GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	//GetMainCameraActorTransform().SetLocalPosition({ -2606 , 1900  , 900 });

	//std::shared_ptr<Player> MainPlayer = CreateActor<Player>();
	//MainPlayer->GetTransform().SetLocalPosition({ -2606, 500, 0 });
}

void Stage_1_3::PlayLevelUpdate(float _DeltaTime)
{
}

void Stage_1_3::End()
{
}

void Stage_1_3::PlayLevelStartEvent()
{
	if (IsLevelFirst_ == false)
	{
		return;
	}

	IsLevelFirst_ = false;

	CreateActor<LevelActor>()->SetLevelMesh("1_3.FBX");

	GlobalIOManager::Load(IOType::SortMap, 2);
	DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	GlobalIOManager::Load(IOType::UnsortMap, 2);
	DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);
	GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	GetMainCameraActorTransform().SetLocalPosition({ -2606 , 1900  , 900 });

	std::shared_ptr<Player> MainPlayer = CreateActor<Player>();
	MainPlayer->GetTransform().SetLocalPosition({ -2606, 500, 0 });
	return;
}