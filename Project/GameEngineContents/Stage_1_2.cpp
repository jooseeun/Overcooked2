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
}

void Stage_1_2::Update(float _DeltaTime)
{
}

void Stage_1_2::End()
{
}