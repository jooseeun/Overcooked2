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

bool GamePlayMoveable::Input_Manual(std::shared_ptr<Player> _Player, float _Delta, float _MaxTime)
{
	CookingGage_ += (_Delta * 100.f) / _MaxTime;

	if (CookingGage_ > 100.f)
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

		return true;
	}
	else
	{
		return false;
	}
}


bool GamePlayMoveable::Input_Auto(float _Delta, float _MaxTime)
{
	CookingGage_ += (_Delta * 100.f) / _MaxTime;

	if (CookingGage_ > 100.f)
	{
		if (TrimmingFirstTime_ == false)
		{
			FinishTrimmingFirst();
			TrimmingFirstTime_ = true;
		}
		else
		{
			FinishTrimming();
		}

		return true;
	}
	else
	{
		return false;
	}
}

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

