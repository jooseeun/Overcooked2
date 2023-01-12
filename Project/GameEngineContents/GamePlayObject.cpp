#include "PreCompile.h"
#include "GamePlayObject.h"
#include "Equipment_Plate.h"


int GamePlayObject::ObjectNumberInServer_ = 100000;
GamePlayObject::GamePlayObject()
	: Mesh_Object_(nullptr)
	, Collision_Object_(nullptr)
	, Enum_ObjectType_(ObjectType::None)
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

void GamePlayObject::ServerStart(int _ParentsID)
{
	if (nullptr != ServerInitManager::Net)
	{
		if (false == GetIsNetInit() && ServerInitManager::Net->GetIsHost())
		{
			std::shared_ptr<ObjectStartPacket> Packet = std::make_shared<ObjectStartPacket>();
			ChildServerStart();    
			//Packet->ObjectToolData = ObjectToolType::None;
			SendObjectType(Packet);
			if (Packet->MapObjData == MapObjType::Max && Packet->ToolData == ToolInfo::None
				&& Packet->IngredientData == IngredientType::None && Packet->ObjectToolData == ObjectToolType::None && Packet->ExceptionData == ExceptionObject::None)
			{
				InitFirst = true;
				return; // 넘길 가치 없는 것들
			}

			Packet->HoldObjectID = GetChildNetID();

			if (Packet->HoldObjectID >= 0)
			{
				int a = 0;
			}

			FindEmptyServerNumber();
			Packet->ObjectID = ObjectNumberInServer_++;

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
	if (nullptr != ServerInitManager::Net)
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
						break;
					}
					if (!ObjectUpdate->Pos.CompareInt3D(float4::ZERO))
					{
						GetTransform().SetWorldPosition(ObjectUpdate->Pos);
						GetTransform().SetWorldRotation(ObjectUpdate->Rot);
						GetTransform().SetWorldScale(ObjectUpdate->Scale);
					}

					break;
				}
				case ContentsPacketType::ObjectInteractUpdate:
				{
					std::shared_ptr<ObjectInteractUpdatePacket> ObjectUpdate = std::dynamic_pointer_cast<ObjectInteractUpdatePacket>(Packet);
					{
						GameServerObject* ServerObject = GameServerObject::GetServerObject(ObjectUpdate->PlayerNum);
						if (Player::GetMyPlayer()->shared_from_this()->CastThis<Player>()->GetNetID() == ObjectUpdate->SendPacktPlayer)
						{
							return;
						}

						if (ServerObject->GetServerType() == ServerObjectType::Player)
						{
							SetPlayerState(static_cast<Player*>(ServerObject)->shared_from_this()->CastThis<Player>(), ObjectUpdate->Type, nullptr, true);
						}
						else if (ServerObject->GetServerType() == ServerObjectType::Object)
						{
							SetPlayerState(nullptr, ObjectUpdate->Type, static_cast<GamePlayMoveable*>(ServerObject)->shared_from_this()->CastThis<GamePlayMoveable>(), true);
						}
						else
						{
							MsgBoxAssert("처리할수 없는 패킷이 날아왔습니다. ObjectInteractUpdate");
						}
					}
				}
				break;
				case ContentsPacketType::ObjectCookingGageUpdate:
				{
					std::shared_ptr<ObjectCookingGagePacket> ObjectUpdate = std::dynamic_pointer_cast<ObjectCookingGagePacket>(Packet);
					SetServerCookingGage(ObjectUpdate);
					//SetServerCookingGage(ObjectUpdate->CookingGage);
				}
				break;
				case ContentsPacketType::ObjectParentsSetFrame:
				{
					std::shared_ptr<ObjectParentsSetAllFramePacket> ParentsSetPacket = std::dynamic_pointer_cast<ObjectParentsSetAllFramePacket>(Packet);


					if (ParentsSetPacket->ChildID == -1)
					{
						SetDeleteChild();
					}
					else
					{
						GameServerObject* FindChildObject = GameServerObject::GetServerObject(ParentsSetPacket->ChildID);
						std::shared_ptr<GamePlayStuff> ChildObject = ((GamePlayObject*)(FindChildObject))->shared_from_this()->CastThis<GamePlayStuff>();
						if (ChildObject == nullptr)
						{
							MsgBoxAssertString("GamePlayObject::ServerUpdate() ChildObject is nullptr / ChildNuber : " + std::to_string(ParentsSetPacket->ChildID))
							return;
						}
						SetChild(ChildObject);
					}


					//SetServerCookingGage(ObjectUpdate->CookingGage);
				}
				break;
				default:
					MsgBoxAssert("처리할수 없는 패킷이 날아왔습니다.");
					break;
				}
			}
		}

		//if (ServerInitManager::Net->GetIsHost())
		//{
		//	std::shared_ptr<ObjectParentsSetAllFramePacket> ParentsSetPacket = std::make_shared<ObjectParentsSetAllFramePacket>();
		//	ParentsSetPacket->ParentsID = GetNetID();
		//	ParentsSetPacket->ChildID = GetChildNetID();
		//	ServerInitManager::Net->SendPacket(ParentsSetPacket);
		//}
	}


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