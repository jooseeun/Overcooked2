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

	//GUI�� ���� �ٷ� ���������� �����Ϸ��ϸ�
	//���ʿ��� ������ LoadingLvel�� ���� �ش� ������ ���ҽ��� �ε��մϴ�.
	GlobalGameData::SetCurStage(GetName());
	GEngine::ChangeLevel("LoadingLevel");
	return;
}