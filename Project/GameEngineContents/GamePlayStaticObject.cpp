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

SetPlayerState_Return GamePlayStaticObject::SetPlayerState(std::shared_ptr<Player> _Player, PlayerCurStateType _Type, std::shared_ptr<GamePlayMoveable> _Moveable, bool _FromNet)
{
	//std::shared_ptr<ObjectUpdatePacket> Packet = std::make_shared<ObjectUpdatePacket>();
	//Packet->ObjectID = GetNetID();
	//Packet->Type = ServerObjectType::Object;
	//Packet->State = IsDeath() ? ServerObjectBaseState::Base : ServerObjectBaseState::Death;
	//Packet->Pos = float4::ZERO;
	//Packet->Rot = float4::ZERO;
	//Packet->Scale = float4::ZERO;
	//Packet->CookingGage = -1;
	//Packet->HoldObjectID = -100;


	if (nullptr != ServerInitManager::Net)
	{
		if (_FromNet == false || ServerInitManager::Net->GetIsHost())
		{
			std::shared_ptr<ObjectInteractUpdatePacket> Packet = std::make_shared<ObjectInteractUpdatePacket>();
			if (_Player != nullptr)
			{
				Packet->PlayerNum = _Player->GetNetID();
			}
			else
			{
				Packet->PlayerNum = _Moveable->GetNetID();
			}

			Packet->Type = _Type;
			Packet->ObjectID = GetNetID();

			if (_FromNet == false)
			{
				Packet->SendPacktPlayer = Player::GetMyPlayer()->GetNetID(); // 직접 움직인곳
			}
			else
			{
				Packet->SendPacktPlayer = _Player->GetNetID(); // 호스트
			}
			
			ServerInitManager::Net->SendPacket(Packet);
		}
	}
	

	SetPlayerState_Return ReturnValue = SetPlayerState_Return::Nothing;
	switch (_Type)
	{
	case PlayerCurStateType::HoldUp:
	{
		if (_Player == nullptr)
		{
			break;
		}
		if (Stuff_Current_ == nullptr)
		{
			break;
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
					ReturnValue = SetPlayerState_Return::Using;
					break;
				default:
					break;
				}
			}
			else
			{
				MsgBoxAssert("GamePlayStaticObject::SetPlayerState case PlayerCurStateType::HoldUp / _Player->GetPlayerHolding() Is not nullptr");
				std::shared_ptr<GamePlayMoveable> Moveable = GetMoveable();
				switch (_Player->GetPlayerHolding()->CastThis<GamePlayMoveable>()->PickUp(&Moveable))
				{
				case HoldDownEnum::HoldUp:
					SetMoveable(Moveable);
					ReturnValue = SetPlayerState_Return::Using;
					break;
				case HoldDownEnum::HoldDown:
				case HoldDownEnum::Nothing:
				default:
					break;
				}
			}
		}
	}
		break;
	case PlayerCurStateType::HoldDown:	
	{		
		if (_Player != nullptr && _Player->GetPlayerHolding() == nullptr)
		{
			break;
		}
		else
		{
			std::shared_ptr<GamePlayMoveable> Moveable = nullptr;
			if (_Player != nullptr)
			{
				Moveable = _Player->GetPlayerHolding()->CastThis<GamePlayMoveable>();
			}
			else if( _Moveable != nullptr)
			{
				Moveable = _Moveable;
			}
			else
			{
				MsgBoxAssert("SetPlayerState -> 둘다 null입니다")
			}

			if (Stuff_Current_ == nullptr)
			{
				std::shared_ptr<GamePlayMoveable> Empty = nullptr;
				switch (Moveable->PickUp(&Empty))
				{
					break;
				case HoldDownEnum::HoldDown:
					if (Empty != nullptr)
					{
						SetStuff(Empty);
						if (_Player != nullptr)
						{
							_Player->CurrentHoldingNull();
						}
						
						ReturnValue = SetPlayerState_Return::Using;
					}
break;
				case HoldDownEnum::HoldUp: // 그릇 전용?
					if (Empty != nullptr)
					{
						SetStuff(Empty);
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
				break;
			case HoldDownEnum::HoldUp:
				if (Moveable == nullptr)
				{
					if (_Player != nullptr)
					{
						_Player->CurrentHoldingNull();
					}
				}
				ReturnValue = SetPlayerState_Return::Using;
				break;
			case HoldDownEnum::HoldDown:
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
		if (_Player == nullptr)
		{
			break;
		}
		if (Stuff_Current_ == nullptr)
		{
			if (_Player->GetPlayerHolding() == nullptr)
			{
				break;
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
				ReturnValue = SetPlayerState_Return::Nothing;
				break;
			case UsingDownEnum::Using:
				ReturnValue = SetPlayerState_Return::Using;
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

	//if (Stuff_Current_ != nullptr)
	//{
	//	Packet->HoldObjectID = GetNetID();
	//}
	//else
	//{
	//	Packet->HoldObjectID = -1;
	//}
	// 
	//if (InteractPacket_ != nullptr)
	//{
	//	ServerInitManager::Net->SendPacket(InteractPacket_);
	//	InteractPacket_.reset();
	//}

	//if (Stuff_Current_ != nullptr)
	//{
	//	std::shared_ptr<ObjectUpdatePacket> StuffPacket = std::make_shared<ObjectUpdatePacket>();
	//	Stuff_Current_->SendDefaultPacket(StuffPacket);
	//	StuffPacket->Pos = float4::ZERO;
	//	StuffPacket->Rot = float4::ZERO;
	//	StuffPacket->Scale = float4::ZERO;
	//	ServerInitManager::Net->SendPacket(StuffPacket);
	//}

	if (nullptr != ServerInitManager::Net && (ServerInitManager::Net->GetIsHost() || _FromNet == false))
	{
		if (_Player->GetPlayerHolding() != nullptr)
		{
			std::shared_ptr<ObjectParentsSetPacket> ParentsSetPacket = std::make_shared<ObjectParentsSetPacket>();
			ParentsSetPacket->ParentsID = _Player->GetNetID();
			ParentsSetPacket->ChildID = _Player->GetPlayerHolding()->CastThis<GamePlayObject>()->GetNetID();

			ServerInitManager::Net->SendPacket(ParentsSetPacket);
		}

		if (Stuff_Current_ != nullptr)
		{
			if (Stuff_Current_->CastThis<GamePlayTool>() != nullptr)
			{
				if (GetMoveable() != nullptr)
				{
					std::shared_ptr<ObjectParentsSetPacket> ToolParentsSetPacket = std::make_shared<ObjectParentsSetPacket>();
					ToolParentsSetPacket->ParentsID = _Player->GetNetID();
					ToolParentsSetPacket->ChildID = GetMoveable()->GetNetID();
					ServerInitManager::Net->SendPacket(ToolParentsSetPacket);
				}
			}

			std::shared_ptr<ObjectParentsSetPacket> ParentsSetPacket = std::make_shared<ObjectParentsSetPacket>();
			ParentsSetPacket->ParentsID = GetNetID();
			ParentsSetPacket->ChildID = Stuff_Current_->GetNetID();

			ServerInitManager::Net->SendPacket(ParentsSetPacket);
		}
	}



	if (ReturnValue == SetPlayerState_Return::Nothing)
	{
		return SetPlayerState_Return::Nothing;
	}
	else
	{
		return SetPlayerState_Return::Using;
	}
	
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
			_Stuff->GetTransform().SetLocalRotation(float4::ZERO);
			_Stuff->SetParent(std::dynamic_pointer_cast<GamePlayObject>(shared_from_this()));
			_Stuff->GetTransform().SetLocalPosition(ToolPos_);
		}
	}


	if (nullptr != ServerInitManager::Net && (ServerInitManager::Net->GetIsHost()))
	{
		std::shared_ptr<ObjectParentsSetPacket> ParentsSetPacket = std::make_shared<ObjectParentsSetPacket>();
		ParentsSetPacket->ParentsID = GetNetID();
		ParentsSetPacket->ChildID = Stuff_Current_->GetNetID();

		ServerInitManager::Net->SendPacket(ParentsSetPacket);	
	}
	
}


