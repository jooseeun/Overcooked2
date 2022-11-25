#include "PreCompile.h"
#include "GamePlayStaticObject.h"
#include "GamePlayStuff.h"
#include "GamePlayMoveable.h"
#include "GamePlayTool.h"

GamePlayStaticObject::GamePlayStaticObject() 
	: Stuff_Current_(nullptr)
	, ToolPos_(float4::ZERO)
{
}

GamePlayStaticObject::~GamePlayStaticObject() 
{
}

void GamePlayStaticObject::Start()
{
	GamePlayObject::Start();
	GamePlayObject::SetObjectType(ObjectType::StaticObject);
	GetCollisionObject()->ChangeOrder(CollisionOrder::Object_StaticObject);
} 

void GamePlayStaticObject::SetBloomEffectOff()
{
	GamePlayObject::SetBloomEffectOff();
	if (Stuff_Current_ != nullptr)
	{
		Stuff_Current_->SetBloomEffectOff();
	}
}

void GamePlayStaticObject::SetBloomEffectOn()
{
	GamePlayObject::SetBloomEffectOn();
	if (Stuff_Current_ != nullptr)
	{
		Stuff_Current_->SetBloomEffectOn();
	}
}

//Input_PutDownOption GamePlayStaticObject::Input_PutDown(std::shared_ptr<GamePlayMoveable> _Object)
//{
//	if (Stuff_Current_ != nullptr)
//	{
//		return Stuff_Current_->Input_PutDown(_Object);
//	}
//	else
//	{
//		Stuff_Current_ = _Object;
//		return Input_PutDownOption::PutDown;
//	}
//}
//
//Input_PickUpOption GamePlayStaticObject::Input_PickUp(std::shared_ptr<Player> _Player)
//{
//	if (Stuff_Current_ != nullptr)
//	{
//		Input_PickUpOption Option = Stuff_Current_->Input_PickUp(_Player);
//		if (Option == Input_PickUpOption::PickUp)
//		{
//			_Player->Input_PickUp(std::dynamic_pointer_cast<GamePlayMoveable>(Stuff_Current_));
//			Stuff_Current_.reset();
//			return Input_PickUpOption::PickUp;
//		}
//		else
//		{
//			return Input_PickUpOption::NoResponse;
//		}
//	}
//	else
//	{
//		return Input_PickUpOption::NoResponse;
//	}
//
//}

SetPlayerState_Return GamePlayStaticObject::SetPlayerState(std::shared_ptr<Player> _Player, PlayerCurStateType _Type)
{
	switch (_Type)
	{
	case PlayerCurStateType::HoldUp:
		if (GetMoveable() != nullptr)
		{
			std::weak_ptr<GamePlayMoveable> Moveable = GetMoveable_TakeOut();
			switch (Moveable.lock()->GetObjectMoveableType())
			{
			case ObjectMoveableType::Food:
				_Player->SetCurHoldType(PlayerHoldType::CanThrow);
				break;
			case ObjectMoveableType::Equipment:
				_Player->SetCurHoldType(PlayerHoldType::NotThrow);
				break;
			default:
				break;
			}
			_Player->SetPlayerHolding(Moveable.lock());
			return SetPlayerState_Return::Using;
		}
		else
		{
			return SetPlayerState_Return::Nothing;
		}
		break;
	case PlayerCurStateType::HoldDown:

		break;
	case PlayerCurStateType::Slice:
		break;
	case PlayerCurStateType::FireOff:
		break;
	case PlayerCurStateType::Throw:
		break;
	default:
		break;
	}
	return SetPlayerState_Return::Nothing;
}

std::shared_ptr<GamePlayMoveable> GamePlayStaticObject::GetMoveable() const
{
	if (Stuff_Current_ == nullptr)
	{
		return nullptr;
	}
	else if (Stuff_Current_->GetObjectStuffType() == ObjectStuffType::Moveable)
	{
		return std::dynamic_pointer_cast<GamePlayMoveable>(Stuff_Current_);
	}
	else
	{
		return std::dynamic_pointer_cast<GamePlayTool>(Stuff_Current_)->GetCurrentMoveable();
	}
}

std::shared_ptr<GamePlayMoveable> GamePlayStaticObject::GetMoveable_TakeOut()
{
	std::weak_ptr<GamePlayMoveable> Moveable;
	if (Stuff_Current_ != nullptr)
	{
		if (Stuff_Current_->GetObjectStuffType() == ObjectStuffType::Moveable)
		{
			Moveable = Stuff_Current_;
			Stuff_Current_ = nullptr;
		}
		else
		{	
			std::weak_ptr<GamePlayTool> Tool_Cast = std::dynamic_pointer_cast<GamePlayTool>(Stuff_Current_);
			Moveable = Tool_Cast.lock()->GetCurrentMoveable();
			Tool_Cast.lock()->ReSetCurrentMoveable();
		}
	}
	return Moveable.lock();
}