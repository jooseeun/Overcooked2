#include "PreCompile.h"
#include "GlobalGameData.h"

std::string GlobalGameData::CurStage_ = "";

std::map<std::string, StageData> GlobalGameData::AllStageData_;

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

	GlobalGameData::AllStageData_.insert(std::make_pair("3-4",
		CreateStageData("3-4", Thema::WizardKitchen)));
}

StageData InitGlobalGameData::CreateStageData(std::string_view _StageName, Thema _StageThema)
{
	StageData NewData;
	NewData.StageName = _StageName;
	NewData.StageThema = _StageThema;
	return NewData;
}

InitGlobalGameData CreatGlobalGameDataInst = InitGlobalGameData();