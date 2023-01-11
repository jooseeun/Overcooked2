#include "PreCompile.h"
#include "InGameUIActor.h"

#include "OverCookedUIRenderer.h"
#include "ServerInitManager.h"
#include <GameEngineBase/GameServerNetServer.h>

#include "GlobalGameData.h"
#include "UIDebugGUI.h"
#include "FadeFont.h"

using namespace ContentsUtility;

InGameUIActor::InGameUIActor()
{
}

InGameUIActor::~InGameUIActor()
{
}

void InGameUIActor::ServerInit()
{
	IsInit_ = true;
	ServerStart();
	if (ServerInitManager::Net->GetIsHost() == true)
	{
		ClientInit(ServerObjectType::UI, 3999);
		ReadySycn_.SetReady(3999, false);
		ReadySycn_.SetHost();
		RecipeManager_.IsHost_ = true;
	}
	else
	{
		int i = 4000;
		for (; ; i++)
		{
			if (GameServerObject::GetServerObject(i) == nullptr)
			{
				ClientInit(ServerObjectType::UI, i);
				ReadySycn_.SetReady(i, false);
				RecipeManager_.IsHost_ = false;
				break;
			}
		}
	}
}

void InGameUIActor::ServerRelease()
{
	EraseServerObject(GetNetID());
}

void InGameUIActor::UIStart()
{
	//Timer
	{
		TimerUIInst_.Banner = CreateUIRenderer("timer_banner_bg.png");
		TimerUIInst_.Banner->GetTransform().SetLocalPosition({ 480.f,-300.f });

		TimerUIInst_.BarBackground = CreateUIRenderer("coin_banner_bar_00.png", 0.78f);
		TimerUIInst_.BarBackground->GetTransform().SetLocalPosition({ 479.f,-316.f });

		TimerUIInst_.Bar = CreateUIRenderer("coin_banner_bar_00.png", 0.78f);
		TimerUIInst_.Bar->GetTransform().SetLocalPosition({ 479.f,-316.f });

		TimerUIInst_.HourGlass = CreateUIRenderer("timer_icon.png");
		TimerUIInst_.HourGlass->GetTransform().SetLocalPosition({ 573.f,-300.f });

		TimerUIInst_.Time = CreateComponent<GameEngineFontRenderer>();
		TimerUIInst_.Time->ChangeCamera(CAMERAORDER::UICAMERA);
		TimerUIInst_.Time->SetText("00:00", "Naughty Squirrel");
		TimerUIInst_.Time->SetColor({ 1.0f,1.0f,1.0f,1 });
		TimerUIInst_.Time->SetSize(30.f);
		TimerUIInst_.Time->SetLeftAndRightSort(LeftAndRightSort::CENTER);
		TimerUIInst_.Time->SetAffectTransform(true);

		//폰트
		TimerUIInst_.Time->GetTransform().SetLocalMove({ 480,-266.f,-1 });
	}

	//스코어 보드
	{
		ScoreUIInst_.Banner = CreateUIRenderer("timer_banner_bg.png");
		ScoreUIInst_.Banner->GetTransform().SetLocalPosition({ -480.f,-300.f });

		ScoreUIInst_.BarBackground = CreateUIRenderer("coin_banner_bar_00.png", 0.78f);
		ScoreUIInst_.BarBackground->GetTransform().SetLocalPosition({ -479.f,-316.f });

		ScoreUIInst_.Bar = CreateUIRenderer("coin_banner_bar_00.png", 0.78f);
		ScoreUIInst_.Bar->GetTransform().SetLocalPosition({ -479.f,-316.f });
		ScoreUIInst_.Bar->UpdateColor({ 166.f / 256.f,198.f / 256.f,217.f / 256.f,0 }, { 1.f,1.f,1.f,0.5f });

		ScoreUIInst_.Coin = CreateComponent<GameEngineUIRenderer>();
		ScoreUIInst_.Coin->SetScaleRatio(1 / 1.5f);
		ScoreUIInst_.Coin->SetScaleModeImage();
		ScoreUIInst_.Coin->CreateFrameAnimationFolder("CoinIdle", GameEngineRenderingEvent("Coin", 0, 0, 0.03f, false));
		ScoreUIInst_.Coin->CreateFrameAnimationFolder("CoinSpin", GameEngineRenderingEvent("Coin", 0.03f, true));
		ScoreUIInst_.Coin->AnimationBindEnd("CoinSpin", [&](const GameEngineRenderingEvent _Desc)
			{
				ScoreUIInst_.Coin->ChangeFrameAnimation("CoinIdle");
			});
		ScoreUIInst_.Coin->ChangeFrameAnimation("CoinIdle");
		ScoreUIInst_.Coin->GetTransform().SetLocalPosition({ -573.f,-300.f,-10 });

		ScoreUIInst_.Score = CreateComponent<GameEngineFontRenderer>();
		ScoreUIInst_.Score->ChangeCamera(CAMERAORDER::UICAMERA);
		ScoreUIInst_.Score->SetText("0", "Naughty Squirrel");
		ScoreUIInst_.Score->SetColor({ 1.0f,1.0f,1.0f,1 });
		ScoreUIInst_.Score->SetSize(30.f);
		ScoreUIInst_.Score->SetLeftAndRightSort(LeftAndRightSort::CENTER);
		ScoreUIInst_.Score->SetAffectTransform(true);
		ScoreUIInst_.Score->GetTransform().SetLocalMove({ -480,-266.f,-1 });

		//ScoreUIInst_.TipGaugeFontBackground->GetTransform().SetLocalMove({ -480,-266.f,-1 });

		ScoreUIInst_.TipGaugeFontFrontground = CreateComponent<GameEngineFontRenderer>();
		ScoreUIInst_.TipGaugeFontFrontground->ChangeCamera(CAMERAORDER::UICAMERA);
		ScoreUIInst_.TipGaugeFontFrontground->SetText("팁 x 2", "Naughty Squirrel");
		ScoreUIInst_.TipGaugeFontFrontground->SetColor({ 1.0f,1.0f,1.0f,1 });
		ScoreUIInst_.TipGaugeFontFrontground->SetSize(13.f);
		ScoreUIInst_.TipGaugeFontFrontground->SetLeftAndRightSort(LeftAndRightSort::CENTER);
		ScoreUIInst_.TipGaugeFontFrontground->SetAffectTransform(true);
		ScoreUIInst_.TipGaugeFontFrontground->GetTransform().SetLocalMove({ -480,-308.f,-1 });
		ScoreUIInst_.TipGaugeFontFrontground->Off();

		ScoreUIInst_.Fire = CreateComponent<GameEngineUIRenderer>();
		ScoreUIInst_.Fire->SetScaleRatio(1.2f);
		ScoreUIInst_.Fire->SetScaleModeImage();
		GameEngineRenderingEvent NewEvent = GameEngineRenderingEvent("UI_FlameHUD_01.png", 0.03f, true);
		NewEvent.Init(0, 58);
		ScoreUIInst_.Fire->CreateFrameAnimationCutTexture("UIFire", NewEvent);
		ScoreUIInst_.Fire->ChangeFrameAnimation("UIFire");
		ScoreUIInst_.Fire->GetTransform().SetLocalPosition({ -460,-187 });
		ScoreUIInst_.Fire->Off();
		//ResistDebug("Fire", ScoreUIInst_.Fire->GetTransform());

		//ScoreUIInst_.Fire->GetTransform().SetLocalPosition({ -573.f,-300.f });

		//ResistDebug("ScoreUIInst_", ScoreUIInst_.TipGaugeFontFrontground->GetTransform());
	}

	//준비 시작 끝 관련
	{
		ReadyRenderer_ = CreateUIRenderer("LevelIntro_Ready_Backdrop.png");

		ReadyTimer_.StartTimer(2.0f);
		ReadyTimer_.SetTimeOverFunc([&]()
			{
				//ReadyRenderer_.lock()->Off();
				ReadySycn_.SetReady(GetNetID(), true);
			});

		StartRenderer_ = CreateUIRenderer("LevelIntro_Go_Backdrop.png");
		StartRenderer_.lock()->StartPump(1.2f, 11.0f);
		StartRenderer_.lock()->Off();

		StartTimer_.StartTimer(2.0f);
		StartTimer_.SetTimeOverFunc([&]()
			{
				StartRenderer_.lock()->Off();
				GlobalGameData::SetGameStart(true);
			});

		TimeUpRenderer_ = CreateUIRenderer("ScoreSummary_TimesUp.png");
		TimeUpRenderer_.lock()->StartPump(1.2f, 11.0f);
		TimeUpRenderer_.lock()->Off();

		TimeUpTimer_.StartTimer(2.0f);
		TimeUpTimer_.SetTimeOverFunc([=]()
			{
				if (nullptr != ServerInitManager::Net)
				{
					if (ServerInitManager::Net->GetIsHost() == true)
					{
						std::shared_ptr<ChangeLevelPacket> Packet = std::make_shared<ChangeLevelPacket>();
						Packet->LevelName = "ResultLevel";
						ServerInitManager::Net->SendPacket(Packet);
					}
					GEngine::ChangeLevel("ResultLevel");
				}
				TimeUpRenderer_.lock()->Off();
			});
	}

	NotDeleteRecipe_Timer_.StartTimer(48.f);
	NotDeleteRecipe_Timer_.SetTimeOverFunc(std::bind(&InGameUIActor::CreateRandomRecipe, this));
	//레시피 매니저
	RecipeManager_.Init(std::dynamic_pointer_cast<InGameUIActor>(shared_from_this()),
		std::bind(&InGameUIActor::HandOverScore, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
		std::bind(&InGameUIActor::FailScore, this, std::placeholders::_1));
	//RecipeManager_.DebugFunction();
	//	RecipeManager_.CreateRecipe(FoodType::FishSushimi);
	//RecipeManager_.CreateRecipe(FoodType::PlainBurger);
	//RecipeManager_.CreateRecipe(FoodType::CarrotDumpling);

	//RecipeManager_.CreateRecipe(FoodType::CheeseBurgerLettuceTomato);
	//RecipeManager_.CreateRecipe(FoodType::CheeseBurger);
}

void InGameUIActor::UIUpdate(float _DeltaTime)
{
	if (IsInit_ == false)
	{
		return;
	}
	UpdateIsStart(_DeltaTime);
	if (GlobalGameData::IsGameStart() == false)
	{
		return;
	}

	ServerUpdate(_DeltaTime);

	if (GlobalGameData::GetLeftTimeRef().IsTimeOver() == true)
	{
		TimeUpRenderer_.lock()->On();
		TimeUpTimer_.Update(_DeltaTime);
		return;
	}
	if (GlobalGameData::GetLeftTimeRef().IsTimeOver() == true)
	{
		GEngine::ChangeLevel("ResultLevel");
	}
	UpdateScore(_DeltaTime);

	RecipeManager_.Update(_DeltaTime);

	//UpdateTime & RecipeSpawn
	UpdateTime(_DeltaTime);
}

void InGameUIActor::UpdateIsStart(float _DeltaTime)
{
	if (TransitionIcon_->IsUpdate() == false && BlackRenderer_->IsUpdate() == false && GlobalGameData::IsGameStart() == false)
	{
		ReadyTimer_.Update(_DeltaTime);
		ReadySycn_.UserCount_ = static_cast<int>(ServerInitManager::Server.GetUserSockets().size()) + 1;

		//내가 호스트면
		if (ServerInitManager::Net->GetIsHost() == true)
		{
			//패킷 수신
			{
				while (false == IsPacketEmpty())
				{
					std::shared_ptr<GameServerPacket> Packet = PopPacket();

					ContentsPacketType PacketType = Packet->GetPacketIDToEnum<ContentsPacketType>();

					switch (PacketType)
					{
					case ContentsPacketType::UIUpdate:
					{
						std::shared_ptr<UIDataPacket> UIUpdate = std::dynamic_pointer_cast<UIDataPacket>(Packet);
						ReadySycn_.SetReady(UIUpdate->ObjectID, UIUpdate->IsReady_);
						break;
					}
					case ContentsPacketType::ClinetInit:
					default:
						MsgBoxAssert("처리할수 없는 패킷이 날아왔습니다.");
						break;
					}
				}
			}
			//패킷 송신
			{
				std::shared_ptr<UIDataPacket> Packet = std::make_shared<UIDataPacket>();
				Packet->IsReady_ = ReadySycn_.IsAllReady();
				Packet->ObjectID = GetNetID();
				ServerInitManager::Net->SendPacket(Packet);
			}
		}
		//내가 클라이언트면
		else
		{
			//패킷 수신
			while (false == IsPacketEmpty())
			{
				std::shared_ptr<GameServerPacket> Packet = PopPacket();
				if (Packet == nullptr)
				{
					return;
				}

				ContentsPacketType PacketType = Packet->GetPacketIDToEnum<ContentsPacketType>();

				switch (PacketType)
				{
				case ContentsPacketType::UIUpdate:
				{
					std::shared_ptr<UIDataPacket> UIUpdate = std::dynamic_pointer_cast<UIDataPacket>(Packet);
					ReadySycn_.SetIsAllReady(UIUpdate->IsReady_);
					break;
				}
				case ContentsPacketType::CreateRecipeData:
				{
					std::shared_ptr<CreateRecipePacket> RecipePacket = std::dynamic_pointer_cast<CreateRecipePacket>(Packet);
					RecipeManager_.CreateRecipe(static_cast<FoodType>(RecipePacket->CreateFoodType));
					break;
				}
				case ContentsPacketType::RecipeTimeUpdate:
				{
					std::shared_ptr<RecipeTimeUpdatePacket> RecipePacket = std::dynamic_pointer_cast<RecipeTimeUpdatePacket>(Packet);
					std::vector<float> Vector;
					Vector.push_back(RecipePacket->Recipe_0);
					Vector.push_back(RecipePacket->Recipe_1);
					Vector.push_back(RecipePacket->Recipe_2);
					Vector.push_back(RecipePacket->Recipe_3);
					Vector.push_back(RecipePacket->Recipe_4);
					RecipeManager_.UpdateFixedTime(Vector);
					break;
				}
				}
			}
			//패킷 송신
			{
				std::shared_ptr<UIDataPacket> Packet = std::make_shared<UIDataPacket>();
				Packet->IsReady_ = ReadySycn_.IsReady(GetNetID());
				Packet->ObjectID = GetNetID();
				ServerInitManager::Net->SendPacket(Packet);
			}
		}
	}

	if (ReadySycn_.IsAllReady() == true)
	{
		ReadyRenderer_.lock()->Off();
		if (StartTimer_.IsTimeOver() == false)
		{
			StartRenderer_.lock()->On();
			StartTimer_.Update(_DeltaTime);
		}
	}
}

void InGameUIActor::UpdateTime(float _DeltaTime)
{
	//UpdateTime
	ContentsUtility::Timer LeftTimer = GlobalGameData::GetLeftTimeRef();

	//NotDeleteRecipe_Timer_.Update(_DeltaTime);
	//LeftTimer.Update(_DeltaTime);
	if (NotDeleteRecipe_Timer_.IsTimeOver() == true)
	{
		NotDeleteRecipe_Timer_.StartTimer();
	}

	//레시피가 1개 이하면 바로 레시피를 추가한다.
	{
		{
			if (RecipeManager_.GetRecipeCount() <= 1)
			{
				CreateRandomRecipe();
			}
		}
	}

	//TimeFont
	TimerUIInst_.Time->SetText(std::to_string(LeftTimer.GetCurTime()), "Naughty Squirrel");
	int Minute = static_cast<int>(LeftTimer.GetCurTime() / 60.f);
	int Seconds = static_cast<int>(LeftTimer.GetCurTime()) % 60;

	if (Minute >= 10) // 11 :
	{
		if (Seconds >= 10) // 11 : 24
		{
			TimerUIInst_.Time->SetText(std::to_string(Minute) + ":" + std::to_string(Seconds), "Naughty Squirrel");
		}
		else // 11 : 02
		{
			TimerUIInst_.Time->SetText(std::to_string(Minute) + ":0" + std::to_string(Seconds), "Naughty Squirrel");
		}
	}
	else // 01 :
	{
		if (Seconds >= 10) // 01 : 11
		{
			TimerUIInst_.Time->SetText("0" + std::to_string(Minute) + ":" + std::to_string(Seconds), "Naughty Squirrel");
		}
		else // 01 : 01
		{
			TimerUIInst_.Time->SetText("0" + std::to_string(Minute) + ":0" + std::to_string(Seconds), "Naughty Squirrel");
		}
	}

	//TimeGauge
	float Percentage = LeftTimer.GetCurTime() / GlobalGameData::GetMaxTime();
	TimerUIInst_.Bar->UpdateLeftToRight(Percentage);
	TimerUIInst_.Bar->UpdateLeftTime(Percentage);

	//LeftTime Under 30
	if (LeftTimer.GetCurTime() < 30.3f)
	{
		Under30_ += _DeltaTime * 2.f;
		if (Under30_ < 1.0f)
		{
			float FontSize = GameEngineMath::Lerp(30.f, 35.f, Under30_);
			TimerUIInst_.Time->SetSize(FontSize);
			float4 Color = float4::Lerp({ 1.0f,1.0f,1.0f,1.0f }, { 111.f / 256.f,59.f / 256.f,42.f / 256.f }, Under30_);
			TimerUIInst_.Time->SetColor(Color);
		}
		else if (Under30_ >= 1.f && Under30_ < 2.f)
		{
			float FontSize = GameEngineMath::Lerp(35.f, 30.f, Under30_ - 1);
			TimerUIInst_.Time->SetSize(FontSize);
			float4 Color = float4::Lerp({ 111.f / 256.f,59.f / 256.f,42.f / 256.f }, { 1.0f,1.0f,1.0f,1.0f }, Under30_ - 1);
			TimerUIInst_.Time->SetColor(Color);
		}
		else
		{
			Under30_ = 0.f;
			TimerUIInst_.Time->SetSize(30.f);
		}
	}
	else
	{
		Under30_ = 0.f;
	}

	//레시피 생성

	//뒤버그
	//if (LeftTimer.GetCurTime() < 30.f)
	//{
	//	if (CurScore_ <= 0)
	//	{
	//		GlobalGameData::AddScore(100);
	//		RecipeManager_.CreateRecipe(FoodType::FishSushimi);
	//	}
	//}
	//if (LeftTimer.GetCurTime() < 20.f)
	//{
	//	if (CurScore_ <= 100)
	//	{
	//		GlobalGameData::AddScore(100);
	//		RecipeManager_.CreateRecipe(FoodType::PrawnSushimi);
	//	}
	//}
}

void InGameUIActor::UpdateScore(float _DeltaTime)
{
	int Score = GlobalGameData::GetScore();
	if (CurScore_ != Score) //이전에 저장된 스코어 값과 현재 가지고 온 스코어 값이 다르다면
	{
		ScoreUIInst_.Coin->ChangeFrameAnimation("CoinSpin");
		CurScore_ = Score;
		ScoreUIInst_.Score->SetText(std::to_string(CurScore_), "Naughty Squirrel");
		IsGetScore_ = true;
	}

	//Score
	if (IsGetScore_ == true)
	{
		GetScoreIter_ += _DeltaTime * 3.f;
		if (GetScoreIter_ < 1.0f)
		{
			float FontSize = GameEngineMath::Lerp(30.f, 35.f, GetScoreIter_);
			ScoreUIInst_.Score->SetSize(FontSize);
			float4 Color = float4::Lerp({ 1.0f,1.0f,1.0f,1.0f }, { 0.f / 256.f,256.f / 256.f,0.f / 256.f }, GetScoreIter_);
			ScoreUIInst_.Score->SetColor(Color);
		}
		else if (GetScoreIter_ >= 1.f && GetScoreIter_ < 2.f)
		{
			float FontSize = GameEngineMath::Lerp(35.f, 30.f, GetScoreIter_ - 1);
			ScoreUIInst_.Score->SetSize(FontSize);
			float4 Color = float4::Lerp({ 0.f / 256.f,256.f / 256.f,0.f / 256.f }, { 1.0f,1.0f,1.0f,1.0f }, GetScoreIter_ - 1);
			ScoreUIInst_.Score->SetColor(Color);
		}
		else
		{
			GetScoreIter_ = 0.f;
			ScoreUIInst_.Score->SetSize(30.f);
			IsGetScore_ = false;
		}
	}

	//ScoreBar
	{
		float Percentage = (static_cast<float>(GlobalGameData::GetTipGaugeCountRef()) / 4.f);
		ScoreUIInst_.Bar->UpdateLeftToRight(Percentage);
	}

	//ScoreTip Font
	{
		if (GlobalGameData::GetTipGaugeCountRef() >= 2)
		{
			ScoreUIInst_.TipGaugeFontFrontground->SetText("팁 x " + std::to_string(GlobalGameData::GetTipGaugeCountRef()), "Naughty Squirrel");
			ScoreUIInst_.TipGaugeFontFrontground->On();
			if (GlobalGameData::GetTipGaugeCountRef() == 4)
			{
				ScoreUIInst_.Fire->On();
			}
			else
			{
				ScoreUIInst_.Fire->Off();
			}
		}
		else
		{
			ScoreUIInst_.TipGaugeFontFrontground->Off();
			ScoreUIInst_.Fire->Off();
		}
	}
}

void InGameUIActor::LevelStartEvent()
{
}

void InGameUIActor::CreateRandomRecipe()
{
	if (ServerInitManager::Net->GetIsHost() == false)
	{
		return;
	}
	if (RecipeManager_.GetRecipeCount() >= 5)
	{
		return;
	}
	std::vector<FoodType> FoodTypes = GlobalGameData::GetCurStage().StageRecipe;

	int RandomValue = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(FoodTypes.size()) - 1);
	NotDeleteRecipe_Timer_.StartTimer();
	RecipeManager_.CreateRecipe(FoodTypes[RandomValue]);
	// Host to Client >> 레시피 생성하라는 패킷 송신
	{
		std::shared_ptr<CreateRecipePacket> Packet = std::make_shared<CreateRecipePacket>();
		Packet->CreateFoodType = static_cast<int>(FoodTypes[RandomValue]);
		ServerInitManager::Net->SendPacket(Packet);
	}
}

bool InGameUIActor::RequestHandOverFood(FoodType _Type)
{
	//if (ServerInitManager::Net->GetIsHost() == true)
	//{
	//	//패킷송신 Host to Client
	//	{
	//		std::shared_ptr<OrderHandOverPacket> Packet = std::make_shared<OrderHandOverPacket>();
	//		Packet->HandOverFoodType = static_cast<int>(_Type);
	//		ServerInitManager::Net->SendPacket(Packet);
	//	}
	//	return  HandOverFood(_Type);
	//}
	//else
	//{
	//	//패킷 송신 Clinet to Host
	//	{
	//		std::shared_ptr<RequestHandOverPacket> Packet = std::make_shared<RequestHandOverPacket>();
	//		Packet->HandOverFoodType = static_cast<int>(_Type);
	//		ServerInitManager::Net->SendPacket(Packet);
	//	}
	//	return true;
	//}
	return  HandOverFood(_Type);
}

bool InGameUIActor::HandOverFood(FoodType _Type)
{
	if (RecipeManager_.HandOver(_Type) == true)
	{
		NotDeleteRecipe_Timer_.StartTimer();
		return true;
	}
	return false;
}

void InGameUIActor::HandOverScore(int _FoodScore, int _FoodTips, bool _IsLeft)
{
	//딸배점수 추가
	int TotalTip;
	if (GlobalGameData::GetTipGaugeCountRef() == 0)
	{
		TotalTip = _FoodTips;
	}
	else
	{
		TotalTip = _FoodTips * GlobalGameData::GetTipGaugeCountRef();
	}
	GlobalGameData::AddScore(_FoodScore, TotalTip);
	int TotalScore = _FoodScore + TotalTip;

	std::weak_ptr<FadeFont> ScoreFont = GetLevel()->CreateActor<FadeFont>();
	ScoreFont.lock()->GetTransform().SetWorldPosition({ -520.f,-190.f });
	ScoreFont.lock()->Init("+" + std::to_string(TotalScore), { 0.f / 256.f,256.f / 256.f,0.f / 256.f }, 42.f);

	//팁 점수 폰트 출력
	{
		std::weak_ptr<FadeFont> TipsFont = GetLevel()->CreateActor<FadeFont>();
		TipsFont.lock()->GetTransform().SetWorldPosition(GlobalGameData::GetCurStage().StageHandOverUIPos);
		//TipsFont.lock()->Debug();
		//ResistDebug("Tips", TipsFont.lock()->GetTransform());

		TipsFont.lock()->Init("+" + std::to_string(TotalTip) + " 팁!", { 0.f / 256.f,256.f / 256.f,0.f / 256.f }, 32.f);
	}

	//가장 왼쪽꺼 제출하는 거면 팁게이지 증가
	{
		if (_IsLeft == true)
		{
			GlobalGameData::GetTipGaugeCountRef()++;
			if (GlobalGameData::GetTipGaugeCountRef() > 4)
			{
				GlobalGameData::GetTipGaugeCountRef() = 4;
			}
		}
		else
		{
			GlobalGameData::GetTipGaugeCountRef() = 0;
		}
	}
}

void InGameUIActor::FailScore(int _FoodScore)//양수를 넣어주세요
{
	//팁게이지 초기화
	GlobalGameData::GetTipGaugeCountRef() = 0;
	//실패점수 추가
	GlobalGameData::AddScore(-_FoodScore);
	int TotalScore = _FoodScore;

	std::weak_ptr<FadeFont> ScoreFont = GetLevel()->CreateActor<FadeFont>();
	ScoreFont.lock()->GetTransform().SetWorldPosition({ -520.f,-190.f });
	ScoreFont.lock()->Init("-" + std::to_string(TotalScore), { 256.f / 256.f,0.f / 256.f,0.f / 256.f }, 42.f);
}

void InGameUIActor::ServerStart()
{
}

void InGameUIActor::ServerUpdate(float _DeltaTime)
{
	if (nullptr == ServerInitManager::Net)
	{
		return;
	}

	//
	if (ServerInitManager::Net->GetIsHost() == true)
	{
		//패킷 수신
		//while (false == IsPacketEmpty())
		//{
		//	std::shared_ptr<GameServerPacket> Packet = PopPacket();

		//	ContentsPacketType PacketType = Packet->GetPacketIDToEnum<ContentsPacketType>();

		//	switch (PacketType)
		//	{
		//	//case ContentsPacketType::RequestHandOver:
		//	//{
		//	//	std::shared_ptr<RequestHandOverPacket> RecipePacket = std::dynamic_pointer_cast<RequestHandOverPacket>(Packet);
		//	//	RequestHandOverFood(static_cast<FoodType>(RecipePacket->HandOverFoodType));
		//	//	//RecipeManager_.CreateRecipe(static_cast<FoodType>(RecipePacket->CreateFoodType));
		//	//	break;
		//	//}
		//	default:
		//		break;
		//	}
		//}
		//패킷  송신 : Global Time
		{
			ContentsUtility::Timer& LeftTimer = GlobalGameData::GetLeftTimeRef();
			NotDeleteRecipe_Timer_.Update(_DeltaTime);
			LeftTimer.Update(_DeltaTime);
			std::shared_ptr<UIDataPacket> Packet = std::make_shared<UIDataPacket>();
			Packet->LeftTime = GlobalGameData::GetLeftTimeRef().GetCurTime();
			Packet->ObjectID = GetNetID();
			//혹시 Ready안된 것을 대비한 예외처리
			Packet->IsReady_ = true;

			std::vector<float> TimeVector = RecipeManager_.GetRecipeTime();
			Packet->Recipe_0 = TimeVector[0];
			Packet->Recipe_1 = TimeVector[1];
			Packet->Recipe_2 = TimeVector[2];
			Packet->Recipe_3 = TimeVector[3];
			Packet->Recipe_4 = TimeVector[4];

			ServerInitManager::Net->SendPacket(Packet);
		}

		return;
	}
	//내가 클라이언트면 패킷 받기
	else
	{
		while (false == IsPacketEmpty())
		{
			std::shared_ptr<GameServerPacket> Packet = PopPacket();
			if (Packet == nullptr)
			{
				return;
			}
			ContentsPacketType PacketType = Packet->GetPacketIDToEnum<ContentsPacketType>();

			switch (PacketType)
			{
			case ContentsPacketType::UIUpdate:
			{
				std::shared_ptr<UIDataPacket> UIUpdate = std::dynamic_pointer_cast<UIDataPacket>(Packet);
				*(GlobalGameData::GetLeftTimeRef().GetCurTimeRef()) = UIUpdate->LeftTime;

				std::vector<float> Vector;
				Vector.push_back(UIUpdate->Recipe_0);
				Vector.push_back(UIUpdate->Recipe_1);
				Vector.push_back(UIUpdate->Recipe_2);
				Vector.push_back(UIUpdate->Recipe_3);
				Vector.push_back(UIUpdate->Recipe_4);
				RecipeManager_.UpdateFixedTime(Vector);

				break;
			}
			case ContentsPacketType::CreateRecipeData:
			{
				std::shared_ptr<CreateRecipePacket> RecipePacket = std::dynamic_pointer_cast<CreateRecipePacket>(Packet);
				RecipeManager_.CreateRecipe(static_cast<FoodType>(RecipePacket->CreateFoodType));
				break;
			}
			default:
				MsgBoxAssert("처리할수 없는 패킷이 날아왔습니다.");
				break;
			}
		}
	}
}