#include "PreCompile.h"
#include "Stage_1_2.h"
#include "Player.h"
#include "Bird_Flying.h"

Stage_1_2::Stage_1_2()
{
}

Stage_1_2::~Stage_1_2()
{
}

void Stage_1_2::PlayLevelStart()
{
	//CreateActor<LevelActor>()->SetLevelMesh("1_2.FBX");

	//GlobalIOManager::Load(IOType::SortMap, 1);
	//DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	//GlobalIOManager::Load(IOType::UnsortMap, 1);
	//DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	//std::shared_ptr<Player> MainPlayer = CreateActor<Player>();
	//MainPlayer->GetTransform().SetLocalPosition({ -1500, 500, 0 });

	//GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	//GetMainCameraActorTransform().SetLocalPosition({ -2509, 2500 , 950 });
}

void Stage_1_2::PlayLevelUpdate(float _DeltaTime)
{
}

void Stage_1_2::End()
{
}

void Stage_1_2::PlayLevelStartEvent()
{
	if (IsLevelFirst_ == false)
	{
		return;
	}

	IsLevelFirst_ = false;
	CreateActor<LevelActor>()->SetLevelMesh("1_2.FBX");

	GlobalIOManager::Load(IOType::SortMap, 1);
	DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	GlobalIOManager::Load(IOType::UnsortMap, 1);
	DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	std::shared_ptr<Player> MainPlayer = CreateActor<Player>();
	MainPlayer->GetTransform().SetLocalPosition({ -1500, 500, 0 });

	std::shared_ptr<Bird_Flying> Pigeon_ = CreateActor<Bird_Flying>();
	Pigeon_->GetTransform().SetLocalPosition({ -700, 800, -500 });
	Pigeon_->GetTransform().SetLocalRotation({0, 10, 0});
	Pigeon_->GetTransform().PixLocalNegativeX();
	Pigeon_->SetStartPosition(Pigeon_->GetTransform().GetLocalPosition());

	GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	GetMainCameraActorTransform().SetLocalPosition({ -2509, 2500 , 950 });
	return;
}