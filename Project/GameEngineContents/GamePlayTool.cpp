#include "PreCompile.h"
#include "GamePlayTool.h"
#include "GamePlayMoveable.h"

GamePlayTool::GamePlayTool()
	: Moveable_Current_(nullptr)
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


HoldDownEnum GamePlayTool::HoldDown(std::shared_ptr<Player> _Player)
{
	std::weak_ptr<GamePlayMoveable> Moveable = std::dynamic_pointer_cast<GamePlayMoveable>(_Player->GetPlayerHolding());
	if (Moveable.lock() == nullptr)
	{
		if (Moveable_Current_ == nullptr)
		{
			return HoldDownEnum::Nothing;
		}
		else
		{
			_Player->SetPlayerHolding(Moveable_Current_);
			return HoldDownEnum::HoldUp_Already;
		}
	}
	else
	{
		if (Moveable_Current_ == nullptr)
		{
			Moveable.lock()->SetParentObject(shared_from_this());
			_Player->DetachPlayerHolding();
			return HoldDownEnum::HoldDown_Already;
		}
		else
		{
			switch (Moveable_Current_->HoldDown(_Player))
			{
			case HoldDownEnum::Nothing:
				return HoldDownEnum::Nothing;
				break;
			case HoldDownEnum::HoldDown:
				MsgBoxAssert("예외처리 대기중")
			case HoldDownEnum::HoldDown_Already:
				return HoldDownEnum::HoldDown_Already;
				break;
			case HoldDownEnum::HoldUp:
				MsgBoxAssert("예외처리 대기중")
			case HoldDownEnum::HoldUp_Already:
				return HoldDownEnum::HoldUp_Already;
				break;
			default:
				break;
			}
		}
	}
	return HoldDownEnum::Nothing;
}

