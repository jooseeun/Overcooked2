#include "PreCompile.h"
#include "SelectStageLevel.h"
#include "SelectStageUIActor.h"
#include "UIDebugGUI.h"
#include "GraphicWindow.h"

#include <GameEngineCore/GlobalVignette.h>
#include <GameEngineCore/GlobalOverlay.h>
#include <GameEngineCore/GlobalBloom.h>

SelectStageLevel::SelectStageLevel()
{
	/*{
		std::shared_ptr<GameEngineCameraActor> CameraActor = CreateActor<GameEngineCameraActor>();
		CameraActor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
		CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		CameraActor->GetCameraComponent()->SetCameraOrder(CAMERAORDER::AboveUICAMERA);
	}*/
}

SelectStageLevel::~SelectStageLevel()
{
}

void SelectStageLevel::Start()
{
	std::shared_ptr<GlobalOverlay> GlobalOverlay_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<GlobalOverlay>();
	std::shared_ptr<GlobalBloom> GlobalBloom_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<GlobalBloom>();
	std::shared_ptr<GlobalVignette> GlobalVignette_ = GetUICamera()->GetCameraRenderTarget()->AddEffect<GlobalVignette>();

	GraphicWindow::Main_ = GameEngineGUI::CreateGUIWindow<GraphicWindow>("GraphicGUI", nullptr);
	GraphicWindow::Main_->SetOverlay(GlobalOverlay_);
	GraphicWindow::Main_->SetBloom(GlobalBloom_);
	GraphicWindow::Main_->SetVignette(GlobalVignette_);

	GraphicWindow::Main_->Off();

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
	GameBgmPlayer::BgmPlayer_->ChangeBgm("Lobby.wav");

	UIDebugGUI::Main_->On();
	GraphicWindow::Main_->On();
	if (SelectStageActor_.lock() == nullptr)
	{
		SelectStageActor_ = CreateActor<SelectStageUIActor>();
		SelectStageActor_.lock()->StartFadeIn();
		//UIActor_->Reset();
	}
}

void SelectStageLevel::LevelEndEvent()
{
	GameBgmPlayer::BgmPlayer_->BgmStop();
	GameBgmPlayer::EffectBgmPlayer_->EffectBgmStop();
	UIDebugGUI::Main_->Off();
	GraphicWindow::Main_->Off();
	if (SelectStageActor_.lock() != nullptr)
	{
		SelectStageActor_.lock()->Death();
		SelectStageActor_.reset();
	}
}