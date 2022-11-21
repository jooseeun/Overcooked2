#include "PreCompile.h"
#include "GamePlayLevel.h"

#include "GlobalGameData.h"
#include "InGameUIActor.h"

#include "UIDebugGUI.h"

GamePlayLevel::GamePlayLevel()
{
}

GamePlayLevel::~GamePlayLevel()
{
}

void GamePlayLevel::Start()
{
	UIActor_ = CreateActor<InGameUIActor>();
	PlayLevelStart();
}

void GamePlayLevel::Update(float _DeltaTime)
{
	PlayLevelUpdate(_DeltaTime);
}

void GamePlayLevel::End()
{
}

void GamePlayLevel::LevelStartEvent()
{
	if (IsLevelStartFirst_ == false)
	{
		//FadeIn이벤트
		UIDebugGUI::Main_->On();
		UIActor_->StartFadeIn();

		//남은시간 초기화
		GlobalGameData::GetLeftTimeRef().StartTimer(300.0f);

		PlayLevelStartEvent();
		return;
	}
	IsLevelStartFirst_ = false;

	//GUI를 통해 바로 스테이지로 진입하려하면
	//최초에는 무조건 LoadingLvel로 가서 해당 레벨의 리소스를 로드합니다.
	GlobalGameData::SetCurStage(GetName());
	GEngine::ChangeLevel("LoadingLevel");
	return;
}

void GamePlayLevel::LevelEndEvent()
{
	UIDebugGUI::Main_->Off();
}