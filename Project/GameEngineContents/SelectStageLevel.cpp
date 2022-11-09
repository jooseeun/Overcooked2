#include "PreCompile.h"
#include "SelectStageLevel.h"
#include "SelectStageUIActor.h"
#include "UIDebugGUI.h"

SelectStageLevel::SelectStageLevel()
{
}

SelectStageLevel::~SelectStageLevel()
{
}

void SelectStageLevel::Start()
{
	SelectStageUIActor* NewActor = CreateActor< SelectStageUIActor>();
	UIDebugGUI::Main_ = GameEngineGUI::CreateGUIWindow<UIDebugGUI>("UIDebugGUI", nullptr);
	UIDebugGUI::Main_->Off();

	//GlobalMouseInput* Mouse = GEngine::GetCurrentLevel()->CreateActor<GlobalMouseInput>();
}

void SelectStageLevel::Update(float _DeltaTime)
{
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