#include "PreCompile.h"
#include "GlobalGameData.h"

std::string GlobalGameData::CurStage_ = "";

std::map<std::string, StageData> GlobalGameData::AllStageData_;

float GlobalGameData::LeftTime_ = 0.f;

GlobalGameData::GlobalGameData()
{
}

GlobalGameData::~GlobalGameData()
{
}

InitGlobalGameData::InitGlobalGameData()
{
	GlobalGameData::AllStageData_.insert(std::make_pair("1-1",
		CreateStageData("1-1", Thema::SushiCity)));

	GlobalGameData::AllStageData_.insert(std::make_pair("1-2",
		CreateStageData("1-2", Thema::SushiCity)));
	GlobalGameData::AllStageData_.insert(std::make_pair("1-3",
		CreateStageData("1-3", Thema::SushiCity)));
	GlobalGameData::AllStageData_.insert(std::make_pair("1-4",
		CreateStageData("1-4", Thema::WizardKitchen)));
}

StageData InitGlobalGameData::CreateStageData(std::string_view _StageName, Thema _StageThema)
{
	StageData NewData;
	NewData.StageName = _StageName;
	NewData.StageThema = _StageThema;
	return NewData;
}

InitGlobalGameData CreatGlobalGameDataInst = InitGlobalGameData();