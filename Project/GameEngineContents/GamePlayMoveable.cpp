#include "PreCompile.h"
#include "GamePlayMoveable.h"
#include "GamePlayEquipment.h"

GamePlayMoveable::GamePlayMoveable()
	: TrimmingFirstTime_(false)
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
	CookingGage_ += _Delta / _MaxTime;
	if (CookingGage_ > 1.0f)
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
