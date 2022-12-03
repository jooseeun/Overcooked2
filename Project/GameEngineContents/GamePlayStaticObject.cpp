#include "PreCompile.h"
#include "GamePlayStaticObject.h"
#include "GamePlayStuff.h"
#include "GamePlayMoveable.h"
#include "GamePlayTool.h"

GamePlayStaticObject::GamePlayStaticObject() 
	: Stuff_Current_(nullptr)
	, ToolPos_({0, 50})
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
	{
		if (Stuff_Current_ == nullptr)
		{
			if (_Player->GetPlayerHolding() != nullptr)
			{
				SetStuff(_Player->GetPlayerHolding()->CastThis<GamePlayStuff>());
				_Player->DetachPlayerHolding();
			}
			else
			{

			}
		}
		else
		{
			switch (Stuff_Current_->HoldOn(_Player))
			{
			case HoldDownEnum::HoldUp:
				if (Stuff_Current_->GetObjectStuffType() == ObjectStuffType::Moveable)
				{
					ReSetStuff();
				}
				return SetPlayerState_Return::Using;
				break;
			case HoldDownEnum::HoldDown:
			case HoldDownEnum::Nothing:
			default:
				return SetPlayerState_Return::Nothing;
				break;
			}
		}
	}
		break;
	case PlayerCurStateType::HoldDown:	
	{
		if (Stuff_Current_ == nullptr)
		{
			if (_Player->GetPlayerHolding() != nullptr)
			{
				SetStuff(_Player->GetPlayerHolding()->CastThis<GamePlayStuff>());
				_Player->DetachPlayerHolding();
				return SetPlayerState_Return::Using;
			}
			else
			{
				MsgBoxAssert("¿À·ù")
			}
		}
		else
		{
			if (_Player->GetPlayerHolding() != nullptr)
			{
				switch (_Player->GetPlayerHolding()->CastThis<GamePlayStuff>()->HoldOn(shared_from_this()->CastThis<GamePlayStaticObject>()))
				{
				case HoldDownEnum::HoldUp:
					_Player->DetachPlayerHolding();
					return SetPlayerState_Return::Using;
					break;
				case HoldDownEnum::HoldDown:
				case HoldDownEnum::Nothing:
				default:
					return SetPlayerState_Return::Nothing;
					break;
				}
			}

		}

	}
		break;
	case PlayerCurStateType::Slice:
	{
		if (Stuff_Current_ == nullptr)
		{
			if (_Player->GetPlayerHolding() == nullptr)
			{
				return SetPlayerState_Return::Nothing;
			}
			else
			{
				//_Player->GetPlayerHolding()->CastThis<GamePlayMoveable>()->UsingDown(_Player);
			}
		}
		else
		{
			switch (Stuff_Current_->UsingDown(_Player))
			{
			case UsingDownEnum::Nothing:
				return SetPlayerState_Return::Nothing;
				break;
			case UsingDownEnum::Using:
				return SetPlayerState_Return::Using;
				break;
			default:
				break;
			}
		}
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