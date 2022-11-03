#include "PreCompile.h"
#include "Stage_1_1.h"
#include "Player.h"
#include "IOManagerWindow.h"

Stage_1_1::Stage_1_1()
{

}

Stage_1_1::~Stage_1_1()
{
}

void Stage_1_1::Start()
{
	CreateActor<LevelActor>()->SetLevelMesh("1_1.FBX");

	Player* MainPlayer = CreateActor<Player>();
	MainPlayer->GetTransform().SetLocalPosition({ -1500, 0, 0 });

	GlobalMouseInput* Mouse = CreateActor<GlobalMouseInput>();
	IOManagerWindow* TmpIOWindow = MapEditorGUI::CreateGUIWindow<IOManagerWindow>("IOManager", nullptr);

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
