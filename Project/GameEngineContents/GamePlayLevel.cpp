#include "PreCompile.h"
#include "GamePlayLevel.h"

#include "GlobalGameData.h"
#include "InGameUIActor.h"

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
		//FadeIn�̺�Ʈ
		UIActor_->StartFadeIn();
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