#include "PreCompile.h"
#include "SelectStageLevel.h"
#include "SelectStageUIActor.h"
#include "UIDebugGUI.h"

SelectStageLevel::SelectStageLevel()
{
	{
		std::shared_ptr<GameEngineCameraActor> CameraActor = CreateActor<GameEngineCameraActor>();
		CameraActor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
		CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		CameraActor->GetCameraComponent()->SetCameraOrder(CAMERAORDER::AboveUICAMERA);
	}
}

SelectStageLevel::~SelectStageLevel()
{
}

void SelectStageLevel::Start()
{
	std::shared_ptr<SelectStageUIActor> NewActor = CreateActor<SelectStageUIActor>();
	UIDebugGUI::Main_ = GameEngineGUI::CreateGUIWindow<UIDebugGUI>("UIDebugGUI", nullptr);
	UIDebugGUI::Main_->Off();

	std::shared_ptr<GlobalMouseInput> Mouse = CreateActor<GlobalMouseInput>();
	Mouse->SetIsUI(true);
}

void SelectStageLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDownKey("FreeCameaOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
		GetUICameraActor()->FreeCameraModeOnOff();
	}
}

void SelectStageLevel::End()
{
}

void SelectStageLevel::LevelStartEvent()
{
	UIDebugGUI::Main_->On();
}

void SelectStageLevel::LevelEndEvent()
{
	UIDebugGUI::Main_->Off();
}