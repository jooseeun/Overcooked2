#include "PreCompile.h"
#include "GameEngineUpdateObject.h"

GameEngineUpdateObject::GameEngineUpdateObject() 
	: IsUpdate_(true)
	, IsDeath_(false)
	, IsReleaseUpdate_(false)
	, AccTime_(0.0f)
	, DeathTime_(0.0f)
	, Order_(0)
	, Parent()
{
}

GameEngineUpdateObject::~GameEngineUpdateObject() 
{
}

void GameEngineUpdateObject::ReleaseHierarchy()
{
	//std::list<std::shared_ptr<GameEngineUpdateObject>>::iterator StartIter = Childs.begin();
	//std::list<std::shared_ptr<GameEngineUpdateObject>>::iterator EndIter = Childs.end();

	//for (; StartIter != EndIter; ++StartIter)
	//{
	//	(*StartIter)->ReleaseHierarchy();
	//}

	// delete this;
}

void GameEngineUpdateObject::SetParent(std::shared_ptr<GameEngineUpdateObject> _Parent)
{
	DetachObject();

	Parent = _Parent;
	Parent.lock()->Childs.push_back(shared_from_this());
}

void GameEngineUpdateObject::DetachObject()
{
	if (nullptr != Parent.lock())
	{
		Parent.lock()->Childs.remove(shared_from_this());
		Parent.reset();
	}
}


void GameEngineUpdateObject::AllUpdate(float _DeltaTime)
{
	AddAccTime(_DeltaTime);
	ReleaseUpdate(_DeltaTime);
	Update(GameEngineTime::GetInst()->GetTimeScale(GetOrder()) * _DeltaTime);



	//if (shared_from_this()->IsDebug() == true )
	//{
	//	int a = 0;
	//}
	std::list<std::shared_ptr<GameEngineUpdateObject>> TempChilds = Childs; // 장중혁 : 디버그용
	
	std::list<std::shared_ptr<GameEngineUpdateObject>>::iterator StartIter = TempChilds.begin();
	std::list<std::shared_ptr<GameEngineUpdateObject>>::iterator EndIter = TempChilds.end();


	for (; StartIter != EndIter;StartIter++)
	{
		if (*StartIter == nullptr)
		{
			continue;
		}
		if (false == (*StartIter)->IsUpdate())
		{
			continue;
		}

		(*StartIter)->AllUpdate(_DeltaTime);
	}

	//for (std::shared_ptr<GameEngineUpdateObject> Com : Childs)
	//{
	//	//Com->AddAccTime(_DeltaTime);
	//	//Com->ReleaseUpdate(_DeltaTime);
	//	if (false == Com->IsUpdate())
	//	{
	//		continue;
	//	}

	//	Com->AllUpdate(_DeltaTime);
	//	
	//
	//}
}

void GameEngineUpdateObject::AllLevelStartEvent()
{
	/*this->*/LevelStartEvent();

	for (std::shared_ptr<GameEngineUpdateObject> Com : Childs)
	{
		if (false == Com->IsUpdate())
		{
			continue;
		}

		Com->AllLevelStartEvent();
	}
}
void GameEngineUpdateObject::AllLevelEndEvent()
{
	/*this->*/LevelEndEvent();

	for (std::shared_ptr<GameEngineUpdateObject> Com : Childs)
	{
		if (false == Com->IsUpdate())
		{
			continue;
		}

		Com->AllLevelEndEvent();
	}
}

void GameEngineUpdateObject::AllOnEvent()
{
	/*this->*/OnEvent();

	for (std::shared_ptr<GameEngineUpdateObject> Com : Childs)
	{
		if (false == Com->IsUpdate())
		{
			continue;
		}

		Com->AllOnEvent();
	}
}

void GameEngineUpdateObject::AllOffEvent()
{
	/*this->*/OffEvent();

	for (std::shared_ptr<GameEngineUpdateObject> Com : Childs)
	{
		if (false == Com->IsUpdate())
		{
			continue;
		}

		Com->AllOffEvent();
	}
}


void GameEngineUpdateObject::ReleaseObject(
	std::list<std::shared_ptr<GameEngineUpdateObject>>& _RelaseList)
{
	if (true == IsDeath())
	{
		DetachObject();
		_RelaseList.push_back(shared_from_this());
		return;
	}

	std::list<std::shared_ptr<GameEngineUpdateObject>>::iterator StartIter = Childs.begin();
	std::list<std::shared_ptr<GameEngineUpdateObject>>::iterator EndIter = Childs.end();

	for ( ; StartIter != EndIter;)
	{
		if (true == (*StartIter)->IsDeath())
		{
			_RelaseList.push_back((*StartIter));

			std::shared_ptr<GameEngineUpdateObject> DeleteObject = (*StartIter);
			++StartIter;
			DeleteObject->DetachObject();
			continue;
		}

		(*StartIter)->ReleaseObject(_RelaseList);
		++StartIter;
	}
}