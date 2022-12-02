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
		std::shared_ptr<GamePlayStuff> PlayerHave = _Player->GetPlayerHolding()->CastThis<GamePlayStuff>();
		if (Stuff_Current_ == nullptr)
		{
			if (PlayerHave != nullptr)
			{
				_Player->DetachPlayerHolding();
				SetStuff(PlayerHave);
			}
		}
		else
		{
			switch (Stuff_Current_->HoldUp(_Player))
			{

			case HoldDownEnum::HoldUp:
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
			
		}
		else
		{
			switch (Stuff_Current_->HoldDown(_Player, CastThis<GamePlayObject>()))
			{
			case HoldDownEnum::Nothing:
				return SetPlayerState_Return::Nothing;
				break;
			case HoldDownEnum::HoldUp:
			default:
				break;
			}
		}

	/*	std::weak_ptr<GamePlayMoveable> Moveable = std::dynamic_pointer_cast<GamePlayMoveable>(_Player->GetPlayerHolding());
		if (Moveable.lock() != nullptr)
		{
			if (GetMoveable() == nullptr)
			{
				if (Stuff_Current_ == nullptr)
				{
					_Player->DetachPlayerHolding();
					SetStuff(Moveable.lock());
				}
				else
				{

					
				}
				return SetPlayerState_Return::Using;
			}
			else
			{
				if (Stuff_Current_->GetObjectStuffType() == ObjectStuffType::Moveable)
				{*/
					//switch (Stuff_Current_->HoldDown(_Player))
					//{
					//case HoldDownEnum::HoldUp:
					//	MsgBoxAssert("예외")
					//case HoldDownEnum::Nothing:
					//case HoldDownEnum::HoldUp_Already:
					//	return SetPlayerState_Return::Nothing;
					//	break;
					//case HoldDownEnum::HoldDown:
					//	MsgBoxAssert("예외")
					//case HoldDownEnum::HoldDown_Already:
					//	return SetPlayerState_Return::Using;
					//	break;
					//default:
					//	break;
					//}
		//		}
		//		else
		//		{

		//		}
		//	}
		//}
		//else
		//{
		//	MsgBoxAssert("처리안된 예외")
		//}
		//

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
			//switch (Stuff_Current_->UsingDown(_Player))
			//{
			//case UsingDownEnum::Nothing:
			//	break;
			//case UsingDownEnum::Using:
			//	break;
			//default:
			//	break;
			//}
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