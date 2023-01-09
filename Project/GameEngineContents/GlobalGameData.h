#pragma once
#include <string>
#include "ContentsUtility.h"
#include "InGameUIActor.h"

enum Thema
{
	SushiCity,
	WizardKitchen
};

struct StageData
{
	std::string StageName; //1-1, 1-2
	Thema StageThema;
	std::vector<FoodType> StageRecipe; //해당 스테이지에 나오는 음식들
	float4 StageHandOverUIPos; //음식을 제출하는 위치 >UI에서
};
class InitGlobalGameData
{
public:
	InitGlobalGameData();
private:
	StageData CreateStageData(std::string_view _StageName, Thema _StageThema, std::vector<FoodType> _StageRecipe, const float4 _StageHandOverUIPos = { 0,0 });
	FoodData CreateFoodData(FoodType _Type, std::vector<IngredientType>& _Ingredient, std::vector<ToolInfo>& _Cookery, int _Score, float _WaitingTime, bool IsCommonCookery = false);
};

class ResultLevelActor;
struct FoodData;
class GlobalGameData
{
	friend InitGlobalGameData;
	friend ResultLevelActor;
private:
	GlobalGameData();
	~GlobalGameData();
	GlobalGameData(const GlobalGameData& _Other) = delete;
	GlobalGameData(const GlobalGameData&& _Other) noexcept = delete;
	GlobalGameData& operator=(const GlobalGameData& _Ohter) = delete;
	GlobalGameData& operator=(const GlobalGameData&& _Other) noexcept = delete;

public:
	static void SetCurStage(std::string_view _StageName) // if 현재 스테이지 1-7 -> _Name = "1-7"
	{
		CurStage_ = _StageName;
	}
	static StageData& GetCurStageRef()
	{
		if (AllStageData_.find(CurStage_) == AllStageData_.end())
		{
			MsgBoxAssertString("셋팅된 CurStage : " + CurStage_ + " 의 데이터가 존재하지 않습니다.");
		}
		return AllStageData_[CurStage_];
	}

	static StageData GetCurStage()
	{
		if (AllStageData_.find(CurStage_) == AllStageData_.end())
		{
			MsgBoxAssertString("셋팅된 CurStage : " + CurStage_ + " 의 데이터가 존재하지 않습니다.");
		}
		return AllStageData_[CurStage_];
	}

	static ContentsUtility::Timer& GetLeftTimeRef()
	{
		return LeftTime_;
	}

	static float GetMaxTime()
	{
		return 3000.f;
	}

	static int GetScore()
	{
		return Score_;
	}

	static void AddScore(int _Value)
	{
		Score_ += _Value;
		if (_Value < 0)
		{
			FailCount_++;
			FailScore_ += -_Value;
		}
		if (Score_ <= 0)
		{
			Score_ = 0;
		}
	}

	static void AddScore(int _FoodScore, int _Tips)
	{
		DeliveredScore_ += _FoodScore;
		DeliveredCount_++;
		Tips_ += _Tips;

		Score_ += _FoodScore + _Tips;
	}

	static void SetScore(int _Value)
	{
		Score_ = _Value;
	}

	static void ResetScore()
	{
		Score_ = 0;
		DeliveredScore_ = 0;
		DeliveredCount_ = 0;
		Tips_ = 0;
		FailScore_ = 0;
		FailCount_ = 0;
		TipGaugeCount_ = 0;
	}

	static FoodData GetFoodData(FoodType _Type)
	{
		return AllFoodData_[_Type];
	}

	static void SetGameStart(bool _IsGameStart)
	{
		IsGameStart_ = _IsGameStart;
	}

	static bool IsGameStart()
	{
		return IsGameStart_;
	}

	static int GetPlayerCount()
	{
		return PlayerCount_;
	}

	static int& GetTipGaugeCountRef()
	{
		return TipGaugeCount_;
	}
private:
	static bool IsGameStart_;
	static std::string CurStage_;

	static std::map<std::string, StageData> AllStageData_;

	static std::map<FoodType, FoodData> AllFoodData_;

	static ContentsUtility::Timer LeftTime_;

	//점수관련
	static int Score_;
	static int DeliveredScore_;
	static int DeliveredCount_;
	static int Tips_;
	static int FailScore_;
	static int FailCount_;
	static int TipGaugeCount_;

public:
	static int StageMoveCount_;

public:
	static int PlayerCount_;

public:

	static float4 DebugValue1_;
	static float4 DebugValue2_;
};

namespace UI_Utility
{
	std::string EnumToString(FoodType _Type);
	std::string EnumToString(ToolInfo _Type);
	std::string EnumToString(IngredientType _Type);
}
