#include "PreCompile.h"
#include "LoadingData.h"

std::map<std::string, std::function<void()>> LoadingData::AllFunc_;

LoadingData::LoadingData()
{
}

LoadingData::~LoadingData()
{
}

void LoadingData::AddFunc(std::string_view _StageName, std::function<void()> _Func)
{
	if (AllFunc_.find(_StageName.data()) != AllFunc_.end())
	{
		MsgBoxAssert("해당 Stage에 리소스로드 함수가 등록된 상태에서 또 함수를 등록하려 했습니다.");
	}

	AllFunc_.insert(std::make_pair(_StageName.data(), _Func));
}

std::function<void()> LoadingData::GetFunc(std::string_view _StageName)
{
	if (AllFunc_.find(_StageName.data()) == AllFunc_.end())
	{
		MsgBoxAssert("_StageName에 해당하는 함수가 등록돼있지 않습니다.");
	}

	return AllFunc_[_StageName.data()];
}