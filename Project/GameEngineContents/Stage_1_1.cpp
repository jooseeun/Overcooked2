#include "PreCompile.h"
#include "Stage_1_1.h"
#include "Player.h"

Stage_1_1::Stage_1_1()
{

}

Stage_1_1::~Stage_1_1()
{
}

void Stage_1_1::Start()
{
	CreateActor<LevelActor>()->SetLevelMesh("1_1.FBX");

	GlobalIOManager::Load(IOType::SortMap, 0);
	DataParser_.SortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	GlobalIOManager::Load(IOType::UnsortMap, 0);
	DataParser_.UnSortMapDataParsing(GlobalIOManager::GetMapDataVector(), this);

	Player* MainPlayer = CreateActor<Player>();
	MainPlayer->GetTransform().SetLocalPosition({ -1400, 500, 200});

	GlobalMouseInput* Mouse = CreateActor<GlobalMouseInput>();

	GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	GetMainCameraActorTransform().SetLocalPosition({ -1400, 2200, 1600 });
}

void Stage_1_1::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDownKey("FreeCameaOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
		GetUICameraActor()->FreeCameraModeOnOff();
	}
}

void Stage_1_1::End()
{
}
