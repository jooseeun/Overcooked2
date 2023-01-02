#include "PreCompile.h"
#include "ResultLevel.h"
#include "UIDebugGUI.h"
#include "GraphicWindow.h"

#include <GameEngineCore/GlobalVignette.h>
#include <GameEngineCore/GlobalOverlay.h>
#include <GameEngineCore/GlobalBloom.h>

#include "ResultLevelActor.h"

ResultLevel::ResultLevel()
{
}

ResultLevel::~ResultLevel()
{
}

void ResultLevel::Start()
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

void ResultLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDownKey("FreeCameaOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
		GetUICameraActor()->FreeCameraModeOnOff();
	}
}

void ResultLevel::End()
{
}

void ResultLevel::LevelStartEvent()
{
	GameBgmPlayer::EffectBgmPlayer_->EffectBgmStop();
	GameBgmPlayer::BgmPlayer_->ChangeBgm("RoundResults.wav");
	UIDebugGUI::Main_->On();
	GraphicWindow::Main_->On();
	if (ResultLevelActor_.lock() == nullptr)
	{
		ResultLevelActor_ = CreateActor<ResultLevelActor>();
	}
}

void ResultLevel::LevelEndEvent()
{
	UIDebugGUI::Main_->Off();
	GraphicWindow::Main_->Off();
	if (ResultLevelActor_.lock() != nullptr)
	{
		ResultLevelActor_.lock()->Death();
		ResultLevelActor_.reset();
	}
}