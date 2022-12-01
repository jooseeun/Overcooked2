#include "PreCompile.h"
#include "GamePlayStuff.h"
#include "Player.h"

GamePlayStuff::GamePlayStuff()
	: Enum_ObjectStuffType_(ObjectStuffType::None)
	, Enum_ToolInfo_(ToolInfo::None)

{
}

GamePlayStuff::~GamePlayStuff() 
{
}

void GamePlayStuff::Start()
{
	GamePlayObject::Start();
	GamePlayObject::SetObjectType(ObjectType::Stuff);
}

SetPlayerState_Return GamePlayStuff::SetPlayerState(std::shared_ptr<Player> _Player, PlayerCurStateType _Type)
{
	switch (_Type)
	{
	case PlayerCurStateType::HoldUp:
	case PlayerCurStateType::HoldDown:
	{
		//switch (HoldDown(_Player))
		//{
		//case HoldDownEnum::HoldDown:
		//case HoldDownEnum::HoldDown_Already:
		//	MsgBoxAssert("플레이어가 오브젝트를 떨어트릴려고 했습니다")
		//	return SetPlayerState_Return::Using;
		//	break;
		//case HoldDownEnum::HoldUp:
		//	_Player->SetPlayerHolding(std::dynamic_pointer_cast<GameEngineActor>(shared_from_this()));
		//	GetCollisionObject()->Off();
		//case HoldDownEnum::HoldUp_Already:
		//	return SetPlayerState_Return::Using;
		//	break;
		//default:
		//	return SetPlayerState_Return::Nothing;
		//	break;
		//};
	}
		break;
	case PlayerCurStateType::Slice:
	case PlayerCurStateType::FireOff:
	case PlayerCurStateType::DishWash:
	case PlayerCurStateType::Throw:
	{
		//switch (UsingDown(_Player))
		//{
		//case UsingDownEnum::Nothing:
		//	return SetPlayerState_Return::Nothing;
		//	break;
		//case UsingDownEnum::Using:
		//	return SetPlayerState_Return::Using;
		//	break;
		//case UsingDownEnum::Throwing:
		//	// 던지다
		//	return SetPlayerState_Return::Using;
		//	break;
		//default:
		//	break;
		//}
	}
		break;
	case PlayerCurStateType::Max:
		break;
	default:
		break;
	}

	return SetPlayerState_Return::Nothing;
}

//void GamePlayStuff::SetParentObject(std::shared_ptr<GameEngineUpdateObject> _Object)
//{
//	std::weak_ptr<GamePlayObject> Object = _Object->CastThis<GamePlayObject>();
//	const float4& Pos = Object.lock()->GetTransform().GetWorldPosition();
//	GetTransform().SetWorldPosition({ Pos.x, Pos.y + 30.f, Pos.z });
//
//	GetCollisionObject()->Off();
//	SetParent(_Object);
//}