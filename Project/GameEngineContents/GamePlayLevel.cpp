#include "PreCompile.h"
#include "GamePlayLevel.h"

#include "GlobalGameData.h"
#include "InGameUIActor.h"

#include "UIDebugGUI.h"
#include "GraphicWindow.h"

GamePlayLevel::GamePlayLevel()
{
}

GamePlayLevel::~GamePlayLevel()
{
}

bool GamePlayLevel::HandOverFood(FoodType _Type)
{
	return	UIActor_->RecipeManager_.HandOver(_Type);
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
	//남은시간 초기화
	GlobalGameData::GetLeftTimeRef().StartTimer(GlobalGameData::GetMaxTime());
	//남은 스코어 초기화
	GlobalGameData::SetScore(0);
	//현재 스테이지로 셋팅
	GlobalGameData::SetCurStage(GetName());

	if (IsLevelStartFirst_ == false)
	{
		//FadeIn이벤트
		UIDebugGUI::Main_->On();
		GraphicWindow::Main_->On();
		UIActor_->StartFadeIn();
		PlayLevelStartEvent();
		return;
	}
	IsLevelStartFirst_ = false;

	//GUI를 통해 바로 스테이지로 진입하려하면
	//최초에는 무조건 LoadingLvel로 가서 해당 레벨의 리소스를 로드합니다.
	GEngine::ChangeLevel("LoadingLevel");
	return;
}

void GamePlayLevel::LevelEndEvent()
{
	GraphicWindow::Main_->Off();

	UIDebugGUI::Main_->Off();
}