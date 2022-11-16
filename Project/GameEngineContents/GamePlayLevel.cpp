#include "PreCompile.h"
#include "GamePlayLevel.h"

#include "GlobalGameData.h"

GamePlayLevel::GamePlayLevel()
{
}

GamePlayLevel::~GamePlayLevel()
{
}

void GamePlayLevel::Start()
{
}

void GamePlayLevel::Update(float _DeltaTime)
{
}

void GamePlayLevel::End()
{
}

void GamePlayLevel::LevelStartEvent()
{
	if (IsLevelStartFirst_ == false)
	{
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