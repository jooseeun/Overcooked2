#include "PreCompile.h"
#include "GamePlayStuff.h"
#include "Player.h"
#include "GamePlayTool.h"

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

SetPlayerState_Return GamePlayStuff::SetPlayerState(std::shared_ptr<Player> _Player, PlayerCurStateType _Type, std::shared_ptr<GamePlayMoveable> _Moveable, bool _FromNet)
{
	switch (_Type)
	{
	case PlayerCurStateType::HoldUp:
	{
		if (_Player->GetPlayerHolding() == nullptr)
		{
		/*	switch (HoldUp(_Player))
			{
			default:
				break;
			}*/
			//if ()
			//{
			//	_Player->SetPlayerHolding(shared_from_this());
			//	return SetPlayerState_Return::Using;
			//}
			//else
			//{
			//	return SetPlayerState_Return::Nothing;
			//}
		}
	}
	case PlayerCurStateType::HoldDown:
	{

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
		//	// ´øÁö´Ù
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