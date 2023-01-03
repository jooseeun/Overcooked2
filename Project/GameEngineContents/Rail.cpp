#include "PreCompile.h"
#include "Rail.h"

Rail::Rail() 
{
}

Rail::~Rail() 
{
}

void Rail::Start()
{
	GamePlayStaticObject::Start();

	GetFBXMesh()->SetFBXMesh("m_sk_conveyor_belt_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	GetFBXMesh()->GetTransform().SetWorldRotation({ 0, 90, 0 });

	GetCollisionObject()->GetTransform().SetWorldScale({ 120, 50, 120 });
	GetCollisionObject()->GetTransform().SetWorldMove({ 0, 25, 0 });

	GetFBXMesh()->SetSubConstantBufferLink(0, "RENDEROPTION", &RenderOptionMyInst, sizeof(RenderOption));

	SetStuff(GetLevel()->CreateActor<Tool_Rail>());
}

void Rail::Update(float _Delta)
{
	GamePlayObject::Update(_Delta);
	RenderOptionMyInst.UV.x += _Delta * 0.3f;

	//GetTransform().SetWorldRotation({ 0, 0, 0 });
	//GameEngineDebug::OutPutString(std::to_string(GetTransform().GetWorldRotation().x) + ", " + std::to_string(GetTransform().GetWorldRotation().y) + ", " + std::to_string(GetTransform().GetWorldRotation().z));
}


Tool_Rail::Tool_Rail()
	:  FirstTimeCheck_(false)
	, MoveTime_(0)
{
}

Tool_Rail::~Tool_Rail()

{
}
void Tool_Rail::Start()
{
	GamePlayTool::Start();
	GamePlayTool::SetInteractOption(AutoOption::Auto);
	GamePlayTool::SetObjectToolType(ObjectToolType::Rail);
}

void Tool_Rail::Update(float _Delta)
{
	GamePlayObject::Update(_Delta);
	if (FirstTimeCheck_ == false)
	{
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalPosition({0, 0, -50});
		Collision->GetTransform().SetWorldScale({50, 50, 100});
		Collision->IsCollision(CollisionType::CT_OBB, CollisionOrder::Object_StaticObject, CollisionType::CT_OBB,
			std::bind(&Tool_Rail::GetFrontStaticObject, this, std::placeholders::_1, std::placeholders::_2));
		Collision->Off();
		Collision->Death();
		Collision = nullptr;

		FirstTimeCheck_ = true;
	}

	//if (ServerInitManager::Net == nullptr || ServerInitManager::Net->GetIsHost())
	{
		if (Front_StaticObject_.lock() != nullptr)
		{
			if (ServerInitManager::Net != nullptr && !ServerInitManager::Net->GetIsHost())
			{
				_Delta = 0;
			}

			if (GetCurrentMoveable() != nullptr)
			{
				if (After_Moveable_.lock() == nullptr)
				{
					After_Moveable_ = GetCurrentMoveable();
					ReSetCurrentMoveable();
					float4 Pos = After_Moveable_.lock()->GetTransform().GetWorldPosition();
					After_Moveable_.lock()->SetParent(Front_StaticObject_.lock());
					After_Moveable_.lock()->GetTransform().SetLocalPosition(Front_StaticObject_.lock()->GetTransform().GetWorldPosition() - Pos);
					After_Moveable_.lock()->GetCollisionObject()->On();
					MoveTime_ = 0;
				}
			}

			if (After_Moveable_.lock() != nullptr)
			{
				if (After_Moveable_.lock()->GetCollisionObject()->IsUpdate())
				{
					MoveTime_ += _Delta;
					After_Moveable_.lock()->GetTransform().SetLocalPosition(float4::LerpLimit((GetTransform().GetWorldPosition()) - (Front_StaticObject_.lock()->GetTransform().GetWorldPosition()), Front_StaticObject_.lock()->GetToolPos(), MoveTime_ / 1.5f));

					if (ServerInitManager::Net != nullptr && ServerInitManager::Net->GetIsHost())
					{
						std::shared_ptr<ObjectCookingGagePacket> Packet = std::make_shared<ObjectCookingGagePacket>();
						Packet->ObjectID = GetNetID();
						Packet->CookingGage = MoveTime_;

						ServerInitManager::Net->SendPacket(Packet);
					}

					if (MoveTime_ > 1.5f)
					{
						//Front_StaticObject_.lock()->SetPlayerState(nullptr, PlayerCurStateType::HoldDown, After_Moveable_.lock());
						Front_StaticObject_.lock()->SetMoveable(After_Moveable_.lock());
						MoveTime_ = 0;
						After_Moveable_.reset();
						if (ServerInitManager::Net->GetIsHost())
						{
							std::shared_ptr<ObjectParentsSetAllFramePacket> ParentsSetPacket = std::make_shared<ObjectParentsSetAllFramePacket>();
							ParentsSetPacket->ParentsID = GetNetID();
							ParentsSetPacket->ChildID = -1;
							ServerInitManager::Net->SendPacket(ParentsSetPacket);
						}
						//ReSetCurrentMoveable();
					}
				}
				else
				{
					After_Moveable_.reset();
				}
			}
		}
	}

}

void Tool_Rail::SetMoveable(std::shared_ptr<GameEngineUpdateObject> _Child)
{
	GamePlayTool::SetMoveable(_Child);

	if (ServerInitManager::Net->GetIsHost())
	{
		std::shared_ptr<ObjectParentsSetAllFramePacket> ParentsSetPacket = std::make_shared<ObjectParentsSetAllFramePacket>();
		ParentsSetPacket->ParentsID = GetNetID();
		ParentsSetPacket->ChildID = GetChildNetID();
		ServerInitManager::Net->SendPacket(ParentsSetPacket);
	}
	_Child->CastThis<GamePlayObject>()->GetCollisionObject()->On();

	//After_Moveable_ = GetCurrentMoveable();
	//float4 Pos = After_Moveable_.lock()->GetTransform().GetWorldPosition();
	//After_Moveable_.lock()->SetParent(Front_StaticObject_.lock());
	//After_Moveable_.lock()->GetTransform().SetLocalPosition(Front_StaticObject_.lock()->GetTransform().GetWorldPosition() - Pos);
	//MoveTime_ = 0;
	
}

HoldDownEnum Tool_Rail::PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable)
{
	switch (GamePlayTool::PickUp(_Moveable))
	{
	case HoldDownEnum::HoldUp:
		//MsgBoxAssert("¹Ì±¸Çö");
		return HoldDownEnum::HoldUp;
		break;
	case HoldDownEnum::HoldDown:
		//if (After_Moveable_.lock() == (*_Moveable))
		//{
		//	After_Moveable_.reset();
		//}
		return HoldDownEnum::HoldDown;
		break;
	default:
		break;
	}
	return HoldDownEnum::Nothing;
}



CollisionReturn Tool_Rail::GetFrontStaticObject(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	if (GetParent() == _Other->GetParent())
	{
		return CollisionReturn::ContinueCheck;
	}
	std::weak_ptr<GamePlayStaticObject> Object = _Other->GetParent()->CastThis<GamePlayStaticObject>();
	if (Object.lock() != nullptr)
	{
		Front_StaticObject_ = Object.lock();
		return CollisionReturn::Break;
	}
	return CollisionReturn::ContinueCheck;
}