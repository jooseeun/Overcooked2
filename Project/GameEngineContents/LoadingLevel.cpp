#include "PreCompile.h"
#include "LoadingLevel.h"
#include "UIDebugGUI.h"

#include "LoadingUIActor.h"

#include "LoadingData.h"

LoadingLevel::LoadingLevel()
{
}

LoadingLevel::~LoadingLevel()
{
}

void LoadingLevel::Start()
{
	UIActor_ = CreateActor<LoadingUIActor>();

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
	UIActor_->StartFadeIn();
	UIActor_->StartLoad();

	//LoadingData::GetFunc("1-1")();
}

void LoadingLevel::LevelEndEvent()
{
	UIDebugGUI::Main_->Off();
}