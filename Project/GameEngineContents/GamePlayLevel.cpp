#include "PreCompile.h"
#include "GamePlayLevel.h"

#include "GlobalGameData.h"
#include "InGameUIActor.h"

#include "UIDebugGUI.h"
#include "GraphicWindow.h"
#include "SoundControlWindow.h"

GamePlayLevel::GamePlayLevel()
	: ObjectManager_(nullptr)
{
}

GamePlayLevel::~GamePlayLevel()
{
}

bool GamePlayLevel::RequestHandOverFood(FoodType _Type)
{
	return	UIActor_->RequestHandOverFood(_Type);
}

void GamePlayLevel::Start()
{
	ObjectManager_ = CreateActor<GamePlayObjectManager>();
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
	//GlobalGameData::SetScore(0);
	GlobalGameData::ResetScore();
	//현재 스테이지로 셋팅
	GlobalGameData::SetCurStage(GetName());
	//아직 게임시작하지 않은 상태
	GlobalGameData::SetGameStart(false);
	if (IsLevelStartFirst_ == false)
	{
		if (UIActor_ == nullptr)
		{
			UIActor_ = CreateActor<InGameUIActor>();
			UIActor_->ServerInit();
		}
		//FadeIn이벤트
		UIDebugGUI::Main_->On();
		GraphicWindow::Main_->On();
		SoundControlWindow::Main_->On();
		UIActor_->StartFadeIn();
		//GlobalGameData::SetGameStart(true);//이거 나중에 지우고, UI 준비땅 후에 시작되게 만들기.
		if (nullptr != ServerInitManager::Net)
		{
			std::shared_ptr<IgnorePacket> Packet = std::make_shared<IgnorePacket>();
			Packet->SetPacketID(ContentsPacketType::ReadyLevel);
			ServerInitManager::Net->SendPacket(Packet);
		}

		PlayLevelStartEvent();
		return;
	}
	IsLevelStartFirst_ = false;

	//GUI를 통해 바로 스테이지로 진입하려하면
	//최초에는 무조건 LoadingLvel로 가서 해당 레벨의 리소스를 로드합니다.
	GEngine::ChangeLevel("LoadingLevel");

	if (nullptr != ServerInitManager::Net)
	{
		if (ServerInitManager::Net->GetIsHost())
		{
			std::shared_ptr<ChangeLevelPacket> Packet = std::make_shared<ChangeLevelPacket>();
			Packet->LevelName = GetName();
			ServerInitManager::Net->SendPacket(Packet);
		}
	}
	return;
}

void GamePlayLevel::LevelEndEvent()
{
	GraphicWindow::Main_->Off();

	UIDebugGUI::Main_->Off();

	if (UIActor_ != nullptr)
	{
		UIActor_->ServerRelease();
		UIActor_->Death();
		UIActor_.reset();
	}
}