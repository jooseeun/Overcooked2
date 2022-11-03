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
}

void Stage_1_4::Update(float _DeltaTime)
{
}

void Stage_1_4::End()
{
}
