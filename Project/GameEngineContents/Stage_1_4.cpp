#include "PreCompile.h"
#include "Stage_1_4.h"

Stage_1_4::Stage_1_4() 
{
}

Stage_1_4::~Stage_1_4() 
{
}

void Stage_1_4::Start()
{
	CreateActor<LevelActor>()->SetLevelMesh("1_4.FBX");

	GlobalIOManager::Load(IOType::UnsortMap, 3);
	DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);
	GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	GetMainCameraActorTransform().SetLocalPosition({ -1173  , 3300   , 2500 });
}

void Stage_1_4::Update(float _DeltaTime)
{
}

void Stage_1_4::End()
{
}
