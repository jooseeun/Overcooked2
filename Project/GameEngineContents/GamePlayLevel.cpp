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
	return	UIActor_->HandOverFood(_Type);
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
	//�����ð� �ʱ�ȭ
	GlobalGameData::GetLeftTimeRef().StartTimer(GlobalGameData::GetMaxTime());
	//���� ���ھ� �ʱ�ȭ
	//GlobalGameData::SetScore(0);
	GlobalGameData::ResetScore();
	//���� ���������� ����
	GlobalGameData::SetCurStage(GetName());
	//���� ���ӽ������� ���� ����
	GlobalGameData::SetGameStart(false);
	if (IsLevelStartFirst_ == false)
	{
		//FadeIn�̺�Ʈ
		UIDebugGUI::Main_->On();
		GraphicWindow::Main_->On();
		UIActor_->StartFadeIn();
		GlobalGameData::SetGameStart(true);//�̰� ���߿� �����, UI �غ� �Ŀ� ���۵ǰ� �����.
		PlayLevelStartEvent();
		return;
	}
	IsLevelStartFirst_ = false;

	//GUI�� ���� �ٷ� ���������� �����Ϸ��ϸ�
	//���ʿ��� ������ LoadingLvel�� ���� �ش� ������ ���ҽ��� �ε��մϴ�.
	GEngine::ChangeLevel("LoadingLevel");

	if (ServerInitManager::Net->GetIsHost())
	{
		std::shared_ptr<ChangeLevelPacket> Packet = std::make_shared<ChangeLevelPacket>();
		Packet->LevelName = GetName();
		ServerInitManager::Net->SendPacket(Packet);
	}

	return;
}

void GamePlayLevel::LevelEndEvent()
{
	GraphicWindow::Main_->Off();

	UIDebugGUI::Main_->Off();
}