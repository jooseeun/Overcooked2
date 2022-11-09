#include "PreCompile.h"
#include "Stage_1_2.h"
#include "Player.h"

Stage_1_2::Stage_1_2()
{
}

Stage_1_2::~Stage_1_2()
{
}

void Stage_1_2::Start()
{
	CreateActor<LevelActor>()->SetLevelMesh("1_2.FBX");

	GlobalIOManager::Load(IOType::SortMap, 1);
	DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	GlobalIOManager::Load(IOType::UnsortMap, 1);
	DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	Player* MainPlayer = CreateActor<Player>();
	MainPlayer->GetTransform().SetLocalPosition({ -1500, 500, 0 });

	GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	GetMainCameraActorTransform().SetLocalPosition({ -2509, 2500 , 950 });
}

void Stage_1_2::Update(float _DeltaTime)
{
}

void Stage_1_2::End()
{
}