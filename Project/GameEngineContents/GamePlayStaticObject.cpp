#include "PreCompile.h"
#include "GamePlayStaticObject.h"
#include "GamePlayStuff.h"
#include "GamePlayMoveable.h"
#include "GamePlayTool.h"

GamePlayStaticObject::GamePlayStaticObject() 
	: Stuff_Current_(nullptr)
	, ToolPos_({0, 50})
	, MyType_(MapObjType::Max)
	, CrashCollision_(nullptr)
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
	CrashCollision_ = CreateComponent<GameEngineCollision>();
	CrashCollision_->GetTransform().SetWorldScale({10, 20, 10});
	CrashCollision_->GetTransform().SetLocalPosition({ 0, 50, 0 });
	CrashCollision_->SetDebugSetting(CollisionType::CT_AABB, {0.8f, 0, 0.5f, 0.5f});
	CrashCollision_->ChangeOrder(CollisionOrder::Object_StaticObject_1);

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
			return SetPlayerState_Return::Nothing;
		}
		else
		{
			if (_Player->GetPlayerHolding() == nullptr)
			{
				std::shared_ptr<GamePlayMoveable> Moveable = nullptr;
				switch (Stuff_Current_->PickUp(&Moveable))
				{
				case HoldDownEnum::HoldDown:
					if (Moveable == nullptr)
					{
						MsgBoxAssert("오류 확인용")
					}
					if (GetStuff()->CastThis<GamePlayTool>() == nullptr)
					{
						ReSetStuff();
					}
		
					_Player->SetPlayerHolding(Moveable);
					_Player->SetCurHoldType(Moveable->GetHoldType());
					return SetPlayerState_Return::Using;
					break;
				default:
					return SetPlayerState_Return::Nothing;
					break;
				}
			}
			else
			{
				MsgBoxAssert("들어올 일 없지만 예외 체크");
				std::shared_ptr<GamePlayMoveable> Moveable = GetMoveable();
				switch (_Player->GetPlayerHolding()->CastThis<GamePlayMoveable>()->PickUp(&Moveable))
				{
				case HoldDownEnum::HoldUp:
					SetMoveable(Moveable);
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
	case PlayerCurStateType::HoldDown:	
	{
		if (_Player->GetPlayerHolding() == nullptr)
		{
			return SetPlayerState_Return::Nothing;
		}
		else
		{
			std::shared_ptr<GamePlayMoveable> Moveable = _Player->GetPlayerHolding()->CastThis<GamePlayMoveable>();
			if (Stuff_Current_ == nullptr)
			{
				std::shared_ptr<GamePlayMoveable> Empty = nullptr;
				switch (Moveable->PickUp(&Empty))
				{
				case HoldDownEnum::Nothing:
					return SetPlayerState_Return::Nothing;
					break;
				case HoldDownEnum::HoldDown:
					if (Empty != nullptr)
					{
						SetStuff(Empty);
						_Player->CurrentHoldingNull();
						return SetPlayerState_Return::Using;
					}
					break;
				case HoldDownEnum::HoldUp: // 그릇 전용?
					if (Empty != nullptr)
					{
						SetStuff(Empty);
						return SetPlayerState_Return::Nothing;
					}
					break;
				default:
					break;
				}
			}
			else
			{
				switch (GetStuff()->PickUp(&Moveable))
				{
				case HoldDownEnum::Nothing:
					return SetPlayerState_Return::Nothing;
					break;
				case HoldDownEnum::HoldUp:
					if (Moveable == nullptr)
					{
						_Player->CurrentHoldingNull();
					}
					return SetPlayerState_Return::Using;
					break;
				case HoldDownEnum::HoldDown:
					return SetPlayerState_Return::Nothing;
					break;
				default:
					break;
				}
			}
		}
	}
		break;
	case PlayerCurStateType::DishWash:
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

//bool GamePlayStaticObject::SetCheckAndPushMoveable(std::shared_ptr<GamePlayMoveable> _Moveable)
//{
//	if (GetMoveable() != nullptr)
//	{
//		return false;
//	}
//
//	if (Stuff_Current_ == nullptr)
//	{
//		SetStuff(_Moveable);
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//
//	
//}

void GamePlayStaticObject::SetMoveable(std::shared_ptr<GamePlayMoveable> _Moveable)
{
	if (Stuff_Current_ == nullptr)
	{
		SetStuff(_Moveable);
	}
	else
	{
		if (Stuff_Current_->CastThis<GamePlayTool>() != nullptr)
		{
			if (_Moveable == nullptr)
			{
				Stuff_Current_->CastThis<GamePlayTool>()->ReSetCurrentMoveable();
			}
			else
			{
				Stuff_Current_->CastThis<GamePlayTool>()->SetMoveable(_Moveable);
			}
		}
		else
		{
			MsgBoxAssert("아직처리하지 않은 예외")
			//Stuff_Current_ = _Moveable;
		}
	}
}

void GamePlayStaticObject::SetStuff(std::shared_ptr<GamePlayStuff> _Stuff)
{
	if (_Stuff == nullptr)
	{
		ReSetStuff();
	}
	if (Stuff_Current_ != nullptr)
	{
		if (Stuff_Current_->CastThis<GamePlayTool>() != nullptr)
		{
			std::shared_ptr<GamePlayMoveable> Stuff = _Stuff->CastThis<GamePlayMoveable>();
			Stuff_Current_->PickUp(&Stuff);
			_Stuff->GetCollisionObject()->Off();
		}
	}
	else
	{
		Stuff_Current_ = _Stuff;
		Stuff_Current_->GetCollisionObject()->Off();
		if (nullptr != _Stuff)
		{
			_Stuff->SetParent(std::dynamic_pointer_cast<GamePlayObject>(shared_from_this()));
			_Stuff->GetTransform().SetLocalPosition(ToolPos_);
		}
	}
}