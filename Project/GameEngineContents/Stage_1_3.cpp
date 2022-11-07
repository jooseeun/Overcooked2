#include "PreCompile.h"
#include "Stage_1_3.h"

Stage_1_3::Stage_1_3() 
{
}

Stage_1_3::~Stage_1_3() 
{
}

void Stage_1_3::Start()
{
	CreateActor<LevelActor>()->SetLevelMesh("1_3.FBX");

	GlobalIOManager::Load(IOType::UnsortMap, 2);
	DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);
}

void Stage_1_3::Update(float _DeltaTime)
{
}

void Stage_1_3::End()
{
}
