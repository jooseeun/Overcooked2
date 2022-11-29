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

void GamePlayStaticObject::SetHighlightEffectOff()
{
	GamePlayObject::SetHighlightEffectOff();
	if (Stuff_Current_ != nullptr)
	{
		Stuff_Current_->SetHighlightEffectOff();
	}
}

void GamePlayStaticObject::SetHighlightEffectOn()
{
	GamePlayObject::SetHighlightEffectOn();
	if (Stuff_Current_ != nullptr)
	{
		Stuff_Current_->SetHighlightEffectOn();
	}
}

SetPlayerState_Return GamePlayStaticObject::SetPlayerState(std::shared_ptr<Player> _Player, PlayerCurStateType _Type)
{
	switch (_Type)
	{
	case PlayerCurStateType::HoldUp:
		if (Stuff_Current_ == nullptr)
		{
			return SetPlayerState_Return::Nothing;
		}
		else
		{
			switch (Stuff_Current_->HoldDown(_Player))
			{
			case HoldDownEnum::Nothing:
				return SetPlayerState_Return::Nothing;
				break;
			case HoldDownEnum::HoldUp:
				_Player->SetPlayerHolding(Stuff_Current_);
				ReSetStuff();
			case HoldDownEnum::HoldUp_Already:
				return SetPlayerState_Return::Using;
				break;
			default:
				MsgBoxAssert("아직 처리하지 않은 예외")
				break;
			}
		}

		//if (GetMoveable() != nullptr)
		//{
		//	std::weak_ptr<GamePlayMoveable> Moveable = GetMoveable_TakeOut();
		//	Moveable.lock()->GetCollisionObject()->Off();
		//	switch (Moveable.lock()->GetObjectMoveableType())
		//	{
		//	case ObjectMoveableType::Food:
		//		_Player->SetCurHoldType(PlayerHoldType::CanThrow);
		//		break;
		//	case ObjectMoveableType::Equipment:
		//		_Player->SetCurHoldType(PlayerHoldType::NotThrow);
		//		break;
		//	default:
		//		break;
		//	}
		//	_Player->SetPlayerHolding(Moveable.lock());
		//	return SetPlayerState_Return::Using;
		//}
		//else
		//{
		//	return SetPlayerState_Return::Nothing;
		//}
		break;
	case PlayerCurStateType::HoldDown:	
	{
		std::weak_ptr<GamePlayMoveable> Moveable = std::dynamic_pointer_cast<GamePlayMoveable>(_Player->GetPlayerHolding());
		if (Moveable.lock() != nullptr)
		{
			if (GetMoveable() == nullptr)
			{
				_Player->DetachPlayerHolding();
				if (Stuff_Current_ == nullptr)
				{
					SetStuff(Moveable.lock());
				}
				else
				{
					Stuff_Current_->SetParentObject(Moveable.lock());
				}
				return SetPlayerState_Return::Using;
			}
			else
			{
				if (Stuff_Current_->GetObjectStuffType() == ObjectStuffType::Moveable)
				{
					switch (Stuff_Current_->HoldDown(_Player))
					{
					case HoldDownEnum::HoldUp:
						MsgBoxAssert("예외")
					case HoldDownEnum::Nothing:
					case HoldDownEnum::HoldUp_Already:
						return SetPlayerState_Return::Nothing;
						break;
					case HoldDownEnum::HoldDown:
						MsgBoxAssert("예외")
					case HoldDownEnum::HoldDown_Already:
						return SetPlayerState_Return::Using;
						break;
					default:
						break;
					}
				}
				else
				{

				}
			}
		}
		else
		{
			MsgBoxAssert("처리안된 예외")
		}
		

	}
		break;
	case PlayerCurStateType::Slice:
	{
		//if (std::dynamic_pointer_cast<GamePlayTool>(Stuff_Current_)->GetObjectToolType())
		//{

		//}
	}
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
			Moveable = std::dynamic_pointer_cast<GamePlayMoveable>(Stuff_Current_);
			Stuff_Current_.reset();
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