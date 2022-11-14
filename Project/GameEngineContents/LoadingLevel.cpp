#include "PreCompile.h"
#include "LoadingLevel.h"
#include "UIDebugGUI.h"

#include "LoadingUIActor.h"

LoadingLevel::LoadingLevel()
{
	{
		std::shared_ptr<GameEngineCameraActor> CameraActor = CreateActor<GameEngineCameraActor>();
		CameraActor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
		CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		CameraActor->GetCameraComponent()->SetCameraOrder(CAMERAORDER::AboveUICAMERA);
	}
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
}

void LoadingLevel::LevelEndEvent()
{
	UIDebugGUI::Main_->Off();
}