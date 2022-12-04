#include "PreCompile.h"
#include "GamePlayMoveable.h"
#include "GamePlayEquipment.h"
#include "GamePlayTool.h"

GamePlayMoveable::GamePlayMoveable()
	: TrimmingFirstTime_(false)
	, CookingGage_(0)
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
}

bool GamePlayMoveable::Input_Manual(std::shared_ptr<Player> _Player, float _Delta, float _MaxTime)
{
	CookingGage_ += _Delta;
	if (CookingGage_ > _MaxTime)
	{
		if (TrimmingFirstTime_ == false)
		{
			// 플레이어, UI에게 끝났다고 신호
			FinishTrimmingFirst();
			TrimmingFirstTime_ = true;
		}
		else
		{
			// 이건 필요한가?????
			FinishTrimming();
		}

		return true;
	}
	else
	{
		return false;
	}
}

HoldDownEnum GamePlayMoveable::HoldOn(std::shared_ptr<GamePlayStaticObject> _Object)
{
	if (_Object->GetStuff() == nullptr)
	{
		_Object->SetStuff(shared_from_this()->CastThis<GamePlayStuff>());
		return HoldDownEnum::HoldDown;
	}
	else
	{
		switch (_Object->GetStuff()->CastThis<GamePlayStuff>()->PickUp(shared_from_this()->CastThis<GamePlayMoveable>()))
		{
		case HoldDownEnum::Nothing:
			return HoldDownEnum::Nothing;
			break;
		case HoldDownEnum::HoldUp:
			if (!IsDeath())
			{
				if (_Object->GetStuff()->CastThis<GamePlayTool>() == nullptr)
				{
					_Object->SetStuff(shared_from_this()->CastThis<GamePlayMoveable>());
				}
			}
			return HoldDownEnum::HoldUp;
			break;
		case HoldDownEnum::HoldDown:
			return HoldDownEnum::HoldDown;
			break;
		default:
			break;
		}
	}
	return HoldDownEnum::Nothing;
}



//SetPlayerState_Return GamePlayMoveable::SetPlayerState(std::shared_ptr<Player> _Player, PlayerCurStateType _Type)
//{
//	switch (_Type)
//	{
//	case PlayerCurStateType::HoldUp:
//	{
//		switch (Enum_ObjectMoveableType_)
//		{
//		case ObjectMoveableType::Food:
//			_Player->SetCurHoldType(PlayerHoldType::CanThrow);
//			break;
//		case ObjectMoveableType::Equipment:
//			_Player->SetCurHoldType(PlayerHoldType::NotThrow);
//			break;
//		default:
//			break;
//		}
//		_Player->SetPlayerHolding(std::dynamic_pointer_cast<GameEngineActor>(shared_from_this()));
//	}
//	break;
//	case PlayerCurStateType::Throw:
//	{
//		if (Enum_ObjectMoveableType_ == ObjectMoveableType::Food)
//		{
//			// 던지다
//		}
//	}
//	break;
//	default:
//		MsgBoxAssert("아직 설정되지 않은 분기")
//			break;
//	}
//
//	return SetPlayerState_Return::Using;
//}
