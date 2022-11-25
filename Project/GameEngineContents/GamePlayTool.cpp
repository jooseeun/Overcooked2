#include "PreCompile.h"
#include "GamePlayTool.h"
#include "GamePlayMoveable.h"

GamePlayTool::GamePlayTool()
	: Moveable_Current_(nullptr)
	, EndCookingTime_(1.f)
	, InteractOption_Current_(AutoOption::NoResponse)
{
}

GamePlayTool::~GamePlayTool()
{
}

// ---------------------------------------Start
void GamePlayTool::Start()
{
	GamePlayStuff::Start();
	GamePlayStuff::SetObjectStuffType(ObjectStuffType::Tool);

}

// ---------------------------------------Update
void GamePlayTool::Update(float _DeltaTime)
{
	if (Moveable_Current_ != nullptr)
	{
		if (InteractOption_Current_ == AutoOption::Auto)
		{
			Input_ActionToAuto_Update(Moveable_Current_, _DeltaTime);
		}

		if (Moveable_Current_->GetCookingTime() >= EndCookingTime_)
		{
			//Input_Action_End(Moveable_Current_);
		}
	}
}


void GamePlayTool::Input_ActionToAuto_Update(std::weak_ptr<GamePlayMoveable> _Moveable, float _DeltaTime)
{
	//_Moveable->PlusCookingTime(_DeltaTime);
}

Input_PickUpOption GamePlayTool::Input_PickUp(std::shared_ptr<GamePlayMoveable> _Object)
{
	if (Moveable_Current_ == nullptr)
	{
		if (CheckMoveable(_Object) == Input_PickUpOption::PickUp)
		{
			Moveable_Current_ = _Object;
			Moveable_Current_->SetParentObject(std::dynamic_pointer_cast<GamePlayObject>(shared_from_this()));
			return Input_PickUpOption::PickUp;
		}
		else
		{
			return Input_PickUpOption::NoResponse;
		}
	}
	else
	{
		return Moveable_Current_->Input_PickUp(_Object);
	}
}

Input_PickUpOption GamePlayTool::Input_PickUp(std::shared_ptr<Player> _Player)
{
	if (Moveable_Current_ != nullptr)
	{
		if (Moveable_Current_->Input_PickUp(_Player) == Input_PickUpOption::PickUp)
		{
			Moveable_Current_.reset();
		}
	}
	return  Input_PickUpOption::NoResponse;

}
Input_PickUpOption GamePlayTool::CheckMoveable(std::shared_ptr<GamePlayMoveable> _Object)
{
	return Input_PickUpOption::PickUp;
}
