#include "PreCompile.h"
#include "Stage_1_2.h"

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

}

void Stage_1_2::Update(float _DeltaTime)
{
}

void Stage_1_2::End()
{
}