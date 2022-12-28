#include "PreCompile.h"
#include "GamePlayObject.h"
#include "Equipment_Plate.h"


int GamePlayObject::ObjectNumber_ = 100000;
GamePlayObject::GamePlayObject()
	: Mesh_Object_(nullptr)
	, Collision_Object_(nullptr)
	, Enum_ObjectType_(ObjectType::None)
	, BloomEffect_(false)
	, InitFirst(false)
{
}

GamePlayObject::~GamePlayObject()
{
	Death();
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

void GamePlayObject::Update(float _DeltaTime)
{
	ServerUpdate(_DeltaTime);
}


// Server

void GamePlayObject::ServerStart()
{
	if (nullptr != ServerInitManager::Net)
	{
		std::shared_ptr<ObjectStartPacket> Packet = std::make_shared<ObjectStartPacket>();
		if (false == GetIsNetInit())
		{
			ChildServerStart();    
			GameServerObject* Object = GameServerObject::GetServerObject(GetNetID());
			for (int i = ObjectNumber_; ; i++)
			{
				Object = GameServerObject::GetServerObject(i);
				if (Object == nullptr)
				{
					ObjectNumber_ = i;
					break;
				}
			}

	

			SendObjectType(Packet);
			if (Packet->MapObjData == MapObjType::Max && Packet->ToolData == ToolInfo::None
				&& Packet->IngredientData == IngredientType::None)
			{
				return; // 넘길 가치 없는 것들
			}

			Packet->HoldObjectID = GetChildNetID();
			Packet->ObjectID = ObjectNumber_++;
			Packet->Type = ServerObjectType::Object;
			Packet->Pos = GetTransform().GetWorldPosition();
			Packet->Rot = GetTransform().GetWorldRotation();
			Packet->Scale = GetTransform().GetWorldScale();

			ClientInit(ServerObjectType::Object, Packet->ObjectID);

			ServerInitManager::Net->SendPacket(Packet);
			InitFirst = true;
		}
	}

}

void GamePlayObject::ServerUpdate(float _DeltaTime)
{
	if (InitFirst == false && false == GetIsNetInit())
	{
		ServerStart();
		InitFirst = true;
		return;
	}
	else 
	{
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
			case ContentsPacketType::ObjectInteractUpdate:
			{
				std::shared_ptr<ObjectInteractUpdatePacket> ObjectUpdate = std::dynamic_pointer_cast<ObjectInteractUpdatePacket>(Packet);
				std::shared_ptr<GamePlayStaticObject> StaticObject = CastThis<GamePlayStaticObject>();

				if (StaticObject == nullptr)
				{
					MsgBoxAssert("StaticObject가 아닙니다");
				}
				else
				{ 
					StaticObject->SetPlayerState(static_cast<Player*>(GameServerObject::GetServerObject(ObjectUpdate->PlayerNum))->shared_from_this()->CastThis<Player>(), ObjectUpdate->Type);
				}
			}
			break;
			default:
				MsgBoxAssert("처리할수 없는 패킷이 날아왔습니다.");
				break;
			}
		}

		if (GetCollisionObject()->IsUpdate())
		{
			
		}
	}
	/*

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
	}*/



}

//void GamePlayObject::SendDefaultPacket(std::shared_ptr<ObjectUpdatePacket> Packet)
//{
//	Packet->ObjectID = GetNetID();
//	Packet->Type = ServerObjectType::Object;
//	Packet->State = IsDeath() ? ServerObjectBaseState::Base : ServerObjectBaseState::Death;
//	Packet->Pos = GetTransform().GetWorldPosition();
//	Packet->Rot = GetTransform().GetWorldRotation();
//	Packet->Scale = GetTransform().GetWorldScale();
//	Packet->CookingGage = -1;
//	Packet->HoldObjectID = -100;
//	SendPacket(Packet);
//};