#include "PreCompile.h"
#include "LoadingLevel.h"
#include "UIDebugGUI.h"

LoadingLevel::LoadingLevel()
{
}

LoadingLevel::~LoadingLevel()
{
}

void LoadingLevel::Start()
{
	//std::shared_ptr<SelectStageUIActor> NewActor = CreateActor<SelectStageUIActor>();

	std::shared_ptr<GlobalMouseInput> Mouse = CreateActor<GlobalMouseInput>();
	Mouse->SetIsUI(true);
}

void LoadingLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDownKey("FreeCameaOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
		GetUICameraActor()->FreeCameraModeOnOff();
	}
}

void LoadingLevel::End()
{
}

void LoadingLevel::LevelStartEvent()
{
	UIDebugGUI::Main_->On();
}

void LoadingLevel::LevelEndEvent()
{
	UIDebugGUI::Main_->Off();
}
