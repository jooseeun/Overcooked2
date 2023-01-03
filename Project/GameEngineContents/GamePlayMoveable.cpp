#include "PreCompile.h"
#include "GamePlayMoveable.h"
#include "GamePlayEquipment.h"
#include "GamePlayTool.h"

GamePlayMoveable::GamePlayMoveable()
	: TrimmingFirstTime_(false)
	, CookingGage_(0)
	, Enum_ObjectMoveableType_(ObjectMoveableType::None)
	, Enum_HoldType_(PlayerHoldType::Max)
	, CookingBar_(nullptr)
//, CookedStat_Current_(CookedStat::Nomal)
{
}

GamePlayMoveable::~GamePlayMoveable()
{
}

void GamePlayMoveable::Start()
{
	GamePlayStuff::Start();
	GamePlayStuff::SetObjectStuffType(ObjectStuffType::Moveable);
	GetCollisionObject()->ChangeOrder(CollisionOrder::Object_Moveable);

	CookingBar_ = GetLevel()->CreateActor<CookingBar>();
	CookingBar_->LinkObject(CastThis<GameEngineActor>(), {0,-40,0}, &CookingGage_, true);

}
void GamePlayMoveable::Update(float _DeltaTime)
{
	GamePlayObject::Update(_DeltaTime);
	if (ServerInitManager::Net->GetIsHost() && GetCollisionObject()->IsUpdate())
	{
		std::shared_ptr<ObjectUpdatePacket> Packet = std::make_shared<ObjectUpdatePacket>();
		Packet->ObjectID = GetNetID();
		Packet->Type = ServerObjectType::Object;
		Packet->State = IsDeath() ? ServerObjectBaseState::Base : ServerObjectBaseState::Death;
		Packet->Pos = GetTransform().GetWorldPosition();
		Packet->Rot = GetTransform().GetWorldRotation();
		Packet->Scale = GetTransform().GetWorldScale();

		ServerInitManager::Net->SendPacket(Packet);
		return;
	}

	

	if (GetParent() == nullptr)
	{
		if (ServerInitManager::Net == nullptr || ServerInitManager::Net->GetIsHost())
		{
			if (GetCollisionObject()->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject_1, CollisionType::CT_OBB,
				[](std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
				{
					std::shared_ptr StaticObject = _Other->GetParent<GamePlayStaticObject>();
					if (StaticObject != nullptr)
					{
						if (StaticObject->SetPlayerState(nullptr, PlayerCurStateType::HoldDown, _This->GetParent<GamePlayMoveable>()) == SetPlayerState_Return::Using)
						{
							return CollisionReturn::Break;
						}
					}

					return CollisionReturn::ContinueCheck;
				}
			))
			{
				return;
			}
			Gravity();

			if (ServerInitManager::Net != nullptr)
			{
				std::shared_ptr<ObjectUpdatePacket> Packet = std::make_shared<ObjectUpdatePacket>();
				Packet->ObjectID = GetNetID();
				Packet->Type = ServerObjectType::Object;
				Packet->State = ServerObjectBaseState::Base;
				Packet->Pos = GetTransform().GetWorldPosition();
				Packet->Rot = GetTransform().GetWorldRotation();
				Packet->Scale = GetTransform().GetWorldScale();

				ServerInitManager::Net->SendPacket(Packet);
			}
		}
		//GameEngineDebug::OutPutString(std::to_string(GetTransform().GetLocalPosition().x) + " + "  + std::to_string(GetTransform().GetLocalPosition().y) + " + " + std::to_string(GetTransform().GetLocalPosition().z));

	}

}

SetPlayerState_Return GamePlayMoveable::SetPlayerState(std::shared_ptr<Player> _Player, PlayerCurStateType _Type, std::shared_ptr<GamePlayMoveable> _Moveable, bool _FromNet)
{
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
				if (_Moveable->GetIsNetInit())
				{
					Packet->PlayerNum = _Moveable->GetNetID();
				}
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


	SetPlayerState_Return Result = SetPlayerState_Return::Nothing;
	switch (_Type)
	{
	case PlayerCurStateType::HoldUp:
	{
		if (_Player->GetPlayerHolding() == nullptr)
		{
			_Player->SetPlayerHolding(shared_from_this());
			_Player->SetCurHoldType(GetHoldType());
		}
		Result = SetPlayerState_Return::Using;
	}
		
		break;
	case PlayerCurStateType::HoldDown:
		break;
	case PlayerCurStateType::Sink:
		break;
	case PlayerCurStateType::Slice:
		break;
	case PlayerCurStateType::FireOff:
		break;
	case PlayerCurStateType::DishWash:
		break;
	case PlayerCurStateType::Throw:
		break;
	default:
		break;
	}


	if (Result == SetPlayerState_Return::Using)
	{
		return SetPlayerState_Return::Using;
	}
	else
	{
		return SetPlayerState_Return::Nothing;
	}

}


bool GamePlayMoveable::Input_Manual(std::shared_ptr<Player> _Player, float _Delta, float _MaxTime)
{
	if (ServerInitManager::Net != nullptr && !ServerInitManager::Net->GetIsHost())
	{
		_Delta = 0;
	}
	CookingGage_ += (_Delta * 100.f) / _MaxTime;
	bool Result = true;
	if (CookingGage_ >= 100.f)
	{
		if (TrimmingFirstTime_ == false)
		{
			// 플레이어, UI에게 끝났다고 신호
			TrimmingFirstTime_ = true;
			FinishTrimmingFirst();
		}
		else
		{
			// 이건 필요한가?????
			FinishTrimming();
		}

		Result = true;
	}
	else
	{
		Result = false;
	}
	SendCookingPacket();
	return Result;
}


bool GamePlayMoveable::Input_Auto(float _Delta, float _MaxTime)
{
	if (ServerInitManager::Net != nullptr && !ServerInitManager::Net->GetIsHost())
	{
		_Delta = 0;
	}
	bool Result = true;
	if (CookingGage_ >= 100.f)
	{
		CookingGage_ += (_Delta * 100.f) / 8.f;
		if (TrimmingFirstTime_ == false)
		{
			FinishTrimmingFirst();
			TrimmingFirstTime_ = true;
		}
		else
		{
			FinishTrimming();
		}

		Result = true;
	}
	else
	{
		CookingGage_ += (_Delta * 100.f) / _MaxTime;
		Result = true;
	}
	SendCookingPacket();
	return Result;
}

//void GamePlayMoveable::CheckCookingGage()
//{
// 
//}




//HoldDownEnum GamePlayMoveable::HoldOn(std::shared_ptr<GamePlayStaticObject> _Object)
//{
//	if (_Object->GetStuff() == nullptr)
//	{
//		_Object->SetStuff(shared_from_this()->CastThis<GamePlayStuff>());
//		return HoldDownEnum::HoldDown;
//	}
//	else
//	{
//		switch (_Object->GetStuff()->CastThis<GamePlayStuff>()->PickUp(shared_from_this()->CastThis<GamePlayMoveable>()))
//		{
//		case HoldDownEnum::Nothing:
//			return HoldDownEnum::Nothing;
//			break;
//		case HoldDownEnum::HoldUp:
//			if (!IsDeath())
//			{
//				if (_Object->GetStuff()->CastThis<GamePlayTool>() == nullptr)
//				{
//					_Object->SetStuff(shared_from_this()->CastThis<GamePlayMoveable>());
//				}
//			}
//			return HoldDownEnum::HoldUp;
//			break;
//		case HoldDownEnum::HoldDown:
//			return HoldDownEnum::HoldDown;
//			break;
//		default:
//			break;
//		}
//	}
//	return HoldDownEnum::Nothing;
//}
//

//void GamePlayMoveable::SendPacket(std::shared_ptr<ObjectUpdatePacket> Packet)
//{
//	Packet->CookingGage = CookingGage_;
//}