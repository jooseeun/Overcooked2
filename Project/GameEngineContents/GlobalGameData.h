#pragma once
#include <string>

enum Thema
{
	SushiCity,
	WizardKitchen
};

struct StageData
{
	std::string StageName; //1-1, 1-2
	Thema StageThema;
};
class InitGlobalGameData
{
public:
	InitGlobalGameData();
private:
	StageData CreateStageData(std::string_view _StageName, Thema _StageThema);
};

class GlobalGameData
{
	friend InitGlobalGameData;
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
		return AllStageData_[CurStage_];
	}

	static StageData GetCurStage()
	{
		return AllStageData_[CurStage_];
	}

private:
	static std::string CurStage_;

	static std::map<std::string, StageData> AllStageData_;
};
