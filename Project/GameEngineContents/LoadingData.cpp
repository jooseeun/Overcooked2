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
		MsgBoxAssert("�ش� Stage�� ���ҽ��ε� �Լ��� ��ϵ� ���¿��� �� �Լ��� ����Ϸ� �߽��ϴ�.");
	}

	AllFunc_.insert(std::make_pair(_StageName.data(), _Func));
}

std::function<void()> LoadingData::GetFunc(std::string_view _StageName)
{
	if (AllFunc_.find(_StageName.data()) == AllFunc_.end())
	{
		MsgBoxAssert("_StageName�� �ش��ϴ� �Լ��� ��ϵ����� �ʽ��ϴ�.");
	}

	return AllFunc_[_StageName.data()];
}