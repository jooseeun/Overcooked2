#include "PreCompile.h"
#include "GamePlayTool.h"
#include "GamePlayMoveable.h"
#include "Player.h"
#include "Equipment_Pot.h"

GamePlayTool::GamePlayTool()
	: Moveable_Current_(nullptr)
	, InteractOption_Current_(AutoOption::NoResponse)
	, Enum_ObjectToolType_(ObjectToolType::None)
	, MoveablePos_({0, 0})
{
}

GamePlayTool::~GamePlayTool()
{
}

// ---------------------------------------Start
void GamePlayTool::Start()
{
	GamePlayStuff::Start();
	GamePlayStuff::SetObjectStuffType(ObjectStuffType::Tool);

}

// ---------------------------------------Update

void GamePlayTool::SetMoveable(std::shared_ptr<Player> _Player)
{
	std::weak_ptr<GameEngineUpdateObject> Object = _Player->GetPlayerHolding();
	_Player->DetachPlayerHolding();
	SetMoveable(Object.lock());
}

void GamePlayTool::SetMoveable(std::shared_ptr<GameEngineUpdateObject> _Child)
{
	std::weak_ptr<GamePlayMoveable> Object = _Child->CastThis<GamePlayMoveable>();
	//float4 Rotation = Object.lock()->GetTransform().GetWorldRotation();
	_Child->SetParent(shared_from_this());
	Moveable_Current_ = Object.lock();
	Object.lock()->GetTransform().SetLocalPosition(MoveablePos_);
	//Object.lock()->GetTransform().SetWorldRotation(Rotation);
	Object.lock()->GetCollisionObject()->Off();

	if (nullptr != ServerInitManager::Net && (ServerInitManager::Net->GetIsHost()))
	{
		std::shared_ptr<ObjectParentsSetPacket> ParentsSetPacket = std::make_shared<ObjectParentsSetPacket>();
		ParentsSetPacket->ParentsID = GetNetID();
		if (!Moveable_Current_->GetIsNetInit())
		{
			Moveable_Current_->ServerStart();
		}

		ParentsSetPacket->ChildID = Moveable_Current_->GetNetID();
		
		

		ServerInitManager::Net->SendPacket(ParentsSetPacket);
	}
}

HoldDownEnum GamePlayTool::PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable)
{
	if ((*_Moveable) != nullptr)
	{
		if (Moveable_Current_ != nullptr) 
		{
			switch (Moveable_Current_->PickUp(_Moveable))
			{
			case HoldDownEnum::Nothing:
			{
				//std::shared_ptr<GamePlayMoveable> Moveable = (shared_from_this()->CastThis<GamePlayMoveable>());
				//switch ((*_Moveable)->PickUp(&Moveable))
				//{
				//case HoldDownEnum::HoldUp:
				//	if (Moveable == nullptr)
				//	{
				//		ReSetCurrentMoveable();
				//	}
				//	return HoldDownEnum::HoldDown;
				//	break;
				//case HoldDownEnum::Nothing:
				//default:
				//	break;
				//}
			}
				break;
			case HoldDownEnum::HoldDown:
				ReSetCurrentMoveable();
				return HoldDownEnum::HoldDown;
				break;
			case HoldDownEnum::HoldUp:
				return HoldDownEnum::HoldUp;
				break;
			default:
				break;
			}
		}
		else
		{
			SetMoveable(*_Moveable);
			(*_Moveable) = nullptr;
			return HoldDownEnum::HoldUp;
		}
	}
	else
	{
		if (Moveable_Current_ != nullptr)
		{
			(*_Moveable) = Moveable_Current_;
			ReSetCurrentMoveable();
			return HoldDownEnum::HoldDown;
		}
	}

	return HoldDownEnum::Nothing;
}


//HoldDownEnum GamePlayTool::HoldUp(std::shared_ptr<Player> _Player)
//{
//	if (Moveable_Current_ != nullptr)
//	{
//		switch (Moveable_Current_->CastThis<GamePlayStuff>()->HoldUp(_Player))
//		{
//		case HoldDownEnum::HoldUpDelete:
//		case HoldDownEnum::HoldUp:
//			ReSetCurrentMoveable();
//			return HoldDownEnum::HoldUp;
//			break;
//		case HoldDownEnum::HoldDown:
//			return HoldDownEnum::HoldDown;
//			break;
//		case HoldDownEnum::Nothing:
//			return HoldDownEnum::Nothing;
//			break;
//		default:
//			return HoldDownEnum::Nothing;
//			break;
//		}
//	}
//	else
//	{
//		return HoldDownEnum::Nothing;
//	}
//};
