#include "PreCompile.h"
#include "InGameUIActor.h"

#include "OverCookedUIRenderer.h"

#include "GlobalGameData.h"
#include "UIDebugGUI.h"

using namespace ContentsUtility;

InGameUIActor::InGameUIActor()
{
}

InGameUIActor::~InGameUIActor()
{
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
		TimerUIInst_.Time->SetText("03:06", "Naughty Squirrel");
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
		ScoreUIInst_.Coin->GetTransform().SetLocalPosition({ -573.f,-300.f });

		ScoreUIInst_.Score = CreateComponent<GameEngineFontRenderer>();
		ScoreUIInst_.Score->ChangeCamera(CAMERAORDER::UICAMERA);
		ScoreUIInst_.Score->SetText("0", "Naughty Squirrel");
		ScoreUIInst_.Score->SetColor({ 1.0f,1.0f,1.0f,1 });
		ScoreUIInst_.Score->SetSize(30.f);
		ScoreUIInst_.Score->SetLeftAndRightSort(LeftAndRightSort::CENTER);
		ScoreUIInst_.Score->SetAffectTransform(true);
		ScoreUIInst_.Score->GetTransform().SetLocalMove({ -480,-266.f,-1 });

		//ResistDebug("Score", ScoreUIInst_.Score->GetTransform());
	}

	NotDeleteRecipe_Timer_.StartTimer(10.f);
	NotDeleteRecipe_Timer_.SetTimeOverFunc(std::bind(&InGameUIActor::CreateRandomRecipe, this));
	//레시피 매니저
	RecipeManager_.Init(std::dynamic_pointer_cast<InGameUIActor>(shared_from_this()));
	RecipeManager_.DebugFunction();
	//	RecipeManager_.CreateRecipe(FoodType::FishSushimi);
	//RecipeManager_.CreateRecipe(FoodType::PlainBurger);
	//RecipeManager_.CreateRecipe(FoodType::CarrotDumpling);

	//RecipeManager_.CreateRecipe(FoodType::CheeseBurgerLettuceTomato);
	//RecipeManager_.CreateRecipe(FoodType::CheeseBurger);
}

void InGameUIActor::UIUpdate(float _DeltaTime)
{
	if (GlobalGameData::IsGameStart() == false)
	{
		return;
	}
	UpdateScore(_DeltaTime);

	RecipeManager_.Update(_DeltaTime);

	//UpdateTime & RecipeSpawn
	UpdateTime(_DeltaTime);
}

void InGameUIActor::UpdateTime(float _DeltaTime)
{
	//UpdateTime
	ContentsUtility::Timer& LeftTimer = GlobalGameData::GetLeftTimeRef();
	NotDeleteRecipe_Timer_.Update(_DeltaTime);
	if (NotDeleteRecipe_Timer_.IsTimeOver() == true)
	{
		NotDeleteRecipe_Timer_.StartTimer();
	}

	//레시피가 1개 이하면 바로 레시피를 추가한다.
	{
		if (RecipeManager_.GetRecipeCount() <= 1)
		{
			CreateRandomRecipe();
		}
	}
	////최초의 Update 전에 레시피 두개를 생성한다.
	//if (LeftTimer.GetCurTime() >= LeftTimer.Default_Time_)
	//{
	//	//CreateRandomRecipe();
	//	CreateRandomRecipe();
	//}

	LeftTimer.Update(_DeltaTime);

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
			float4 Color = float4::Lerp({ 1.0f,1.0f,1.0f,1.0f }, { 111.f / 256.f,59.f / 256.f,42.f / 256.f }, GetScoreIter_);
			ScoreUIInst_.Score->SetColor(Color);
		}
		else if (GetScoreIter_ >= 1.f && GetScoreIter_ < 2.f)
		{
			float FontSize = GameEngineMath::Lerp(35.f, 30.f, GetScoreIter_ - 1);
			ScoreUIInst_.Score->SetSize(FontSize);
			float4 Color = float4::Lerp({ 111.f / 256.f,59.f / 256.f,42.f / 256.f }, { 1.0f,1.0f,1.0f,1.0f }, GetScoreIter_ - 1);
			ScoreUIInst_.Score->SetColor(Color);
		}
		else
		{
			GetScoreIter_ = 0.f;
			ScoreUIInst_.Score->SetSize(30.f);
			IsGetScore_ = false;
		}
	}
}

void InGameUIActor::LevelStartEvent()
{
	if (GlobalGameData::IsGameStart() == true)
	{
	}
}

void InGameUIActor::CreateRandomRecipe()
{
	if (RecipeManager_.GetRecipeCount() >= 5)
	{
		return;
	}
	std::vector<FoodType> FoodTypes = GlobalGameData::GetCurStage().StageRecipe;

	int RandomValue = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(FoodTypes.size()) - 1);
	NotDeleteRecipe_Timer_.StartTimer();
	RecipeManager_.CreateRecipe(FoodTypes[RandomValue]);
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