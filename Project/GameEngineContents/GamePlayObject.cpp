#include "PreCompile.h"
#include "GamePlayObject.h"

GamePlayObject::GamePlayObject()
	: Mesh_Object_(nullptr)
	, Collision_Object_(nullptr)
	, Enum_ObjectType_(ObjectType::None)
	, BloomEffect_(false)
{
}

GamePlayObject::~GamePlayObject()
{
}

void GamePlayObject::Start()
{
	Mesh_Object_ = CreateComponent<GameEngineFBXStaticRenderer>("Mesh_Object");
	Collision_Object_ = CreateComponent<GameEngineCollision>("Collision_Object");
	Collision_Object_->SetDebugSetting(CollisionType::CT_AABB, { 0, 0.8f, 0, 0.5f });
	Collision_Object_->ChangeOrder(CollisionOrder::Object_None);

	AnimationMesh_Obejct_ = CreateComponent<GameEngineFBXAnimationRenderer>("AnimationMesh_Obejct");
	SetGravityCollision(Collision_Object_);
}

// Server

void GamePlayObject::ServerStart()
{
	//if (false == OnePlayerInit)
	//{
	//	IsPlayerble = true;
	//	OnePlayerInit = true;

	//}

	//if (GetLevel()->GetName() == "TITLELEVEL")
	//{
	//	PlayerPNum = GetNetID();
	//	ChangePlayerColor();
	//}
}

void GamePlayObject::ServerUpdate(float _DeltaTime)
{
	if (false == GetIsNetInit())
	{
		return;
	}

	while (false == IsPacketEmpty())
	{
		std::shared_ptr<GameServerPacket> Packet = PopPacket();

		ContentsPacketType PacketType = Packet->GetPacketIDToEnum<ContentsPacketType>();

		switch (PacketType)
		{
		case ContentsPacketType::ObjectUpdate:
		{
			std::shared_ptr<ObjectUpdatePacket> ObjectUpdate = std::dynamic_pointer_cast<ObjectUpdatePacket>(Packet);
			if (ObjectUpdate->State == ServerObjectBaseState::Death)
			{
				Death();
				Off();
				continue;
			}
			if (!ObjectUpdate->Pos.CompareInt3D(float4::ZERO))
			{
				GetTransform().SetWorldPosition(ObjectUpdate->Pos);
				GetTransform().SetWorldRotation(ObjectUpdate->Rot);
				GetTransform().SetWorldScale(ObjectUpdate->Scale);
			}

			{
				if (0 <= ObjectUpdate->CookingGage)
				{
					SetServerCookingGage(ObjectUpdate->CookingGage);
				}
				if (-1 <= ObjectUpdate->HoldObjectID)
				{
					SetServerHoldObject(ObjectUpdate->HoldObjectID);
				}
			}

			break;
		}
		case ContentsPacketType::ClinetInit:
		default:
			MsgBoxAssert("처리할수 없는 패킷이 날아왔습니다.");
			break;
		}
	}
	if (InteractPacket_ != nullptr)
	{
		ServerInitManager::Net->SendPacket(InteractPacket_);
		InteractPacket_.reset();
	}
	else if (nullptr != ServerInitManager::Net)
	{
		if (ServerInitManager::Net->GetIsHost() && GetCollisionObject()->IsUpdate())
		{
			std::shared_ptr<ObjectUpdatePacket> Packet = std::make_shared<ObjectUpdatePacket>();
			SendDefaultPacket(Packet);

			ServerInitManager::Net->SendPacket(Packet);
			return;
		}
	}
	else
	{
		return;
	}



}

void GamePlayObject::SendDefaultPacket(std::shared_ptr<ObjectUpdatePacket> Packet)
{
	Packet->ObjectID = GetNetID();
	Packet->Type = ServerObjectType::Object;
	Packet->State = IsDeath() ? ServerObjectBaseState::Base : ServerObjectBaseState::Death;
	Packet->Pos = GetTransform().GetWorldPosition();
	Packet->Rot = GetTransform().GetWorldRotation();
	Packet->Scale = GetTransform().GetWorldScale();
	Packet->CookingGage = -1;
	Packet->HoldObjectID = -100;
	SendPacket(Packet);
};