#include "PreCompile.h"
#include "GamePlayTool.h"
#include "GamePlayMoveable.h"
#include "Player.h"

GamePlayTool::GamePlayTool()
	: Moveable_Current_(nullptr)
	, InteractOption_Current_(AutoOption::NoResponse)
	, MoveablePos_({0, 0})
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



void GamePlayTool::SetMoveable(std::shared_ptr<Player> _Player)
{
	std::weak_ptr<GameEngineUpdateObject> Object = _Player->GetPlayerHolding();
	_Player->DetachPlayerHolding();
	SetMoveable(Object.lock());
}

void GamePlayTool::SetMoveable(std::shared_ptr<GameEngineUpdateObject> _Child)
{
	_Child->SetParent(shared_from_this());
	std::weak_ptr<GamePlayMoveable> Object = _Child->CastThis<GamePlayMoveable>();
	Moveable_Current_ = Object.lock();
	Object.lock()->GetTransform().SetLocalPosition(MoveablePos_);
	Object.lock()->GetCollisionObject()->Off();
}

HoldDownEnum GamePlayTool::HoldOn(std::shared_ptr<Player> _Player)
{
	if (Moveable_Current_ != nullptr)
	{
		switch (Moveable_Current_->HoldOn(_Player))
		{
		case HoldDownEnum::Nothing:
			return HoldDownEnum::Nothing;
			break;
		case HoldDownEnum::HoldUp:
			ReSetCurrentMoveable();
			return HoldDownEnum::HoldUp;
			break;
		case HoldDownEnum::HoldDown:
			return HoldDownEnum::HoldDown;
			break;
		default:
			break;
		}
	}
	else
	{
		return HoldDownEnum::Nothing;
	}
};


HoldDownEnum GamePlayTool::PickUp(std::shared_ptr<GamePlayMoveable> _Moveable)
{
	if (GetCurrentMoveable() == nullptr)
	{
		SetMoveable(_Moveable);
		return HoldDownEnum::HoldUp;
	}
	return HoldDownEnum::Nothing;
}


//HoldDownEnum GamePlayTool::HoldUp(std::shared_ptr<Player> _Player)
//{
//	if (Moveable_Current_ != nullptr)
//	{
//		switch (Moveable_Current_->CastThis<GamePlayStuff>()->HoldUp(_Player))
//		{
//		case HoldDownEnum::HoldUpDelete:
//		case HoldDownEnum::HoldUp:
//			ReSetCurrentMoveable();
//			return HoldDownEnum::HoldUp;
//			break;
//		case HoldDownEnum::HoldDown:
//			return HoldDownEnum::HoldDown;
//			break;
//		case HoldDownEnum::Nothing:
//			return HoldDownEnum::Nothing;
//			break;
//		default:
//			return HoldDownEnum::Nothing;
//			break;
//		}
//	}
//	else
//	{
//		return HoldDownEnum::Nothing;
//	}
//};
