#include "PreCompile.h"
#include "IcePlatform.h"

IcePlatform::IcePlatform() 
	: MoveDir_({0.f, 0.f, 230.f})

{
}

IcePlatform::~IcePlatform()
{
}

void IcePlatform::Start()
{
	GamePlayFloor::Start();

	GetFBXMesh()->SetFBXMesh("m_dlc09_iceplatform_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });

	GetCollisionObject()->GetTransform().SetWorldScale({257.f, 200.f, 514.f});
	GetCollisionObject()->GetTransform().SetLocalMove({ -30.f, 0.f, 0.f });

	std::shared_ptr<GameEngineCollision> PlusCol = CreateComponent<GameEngineCollision>();
	PlusCol->GetTransform().SetLocalScale({ 180.00,200.00,514.00 });
	PlusCol->GetTransform().SetLocalPosition(GetTransform().GetWorldPosition() + float4{ -15,100,0 });
	PlusCol->ChangeOrder(CollisionOrder::Map_IcePlatform);
}

void IcePlatform::Update(float _DeltaTime)
{
	GamePlayObject::Update(_DeltaTime);

	//if (IsFirst_ == true) // Lerp 계산
	//{
	//	float Z = GetTransform().GetWorldPosition().z;
	//	IsFirst_ = false;
	//}
	if ((ServerInitManager::Net == nullptr || ServerInitManager::Net->GetIsHost())) // 호스트이거나 솔로플레이던가
	{
		if (GetTransform().GetWorldPosition().z > 1329.f)
		{
			GetTransform().SetWorldPosition({ -1984.f, -100.f, -2722.f });
		}
		else
		{

			GetTransform().SetWorldMove({ MoveDir_ * _DeltaTime });
		}


		// 네트워크렉 안걸린다면
		{
			std::shared_ptr<ObjectUpdatePacket> Packet = std::make_shared<ObjectUpdatePacket>();
			Packet->ObjectID = GetNetID();
			Packet->Type = ServerObjectType::Object;
			Packet->State = ServerObjectBaseState::Base;
			Packet->Pos = GetTransform().GetWorldPosition();
			Packet->Rot = GetTransform().GetWorldRotation();
			Packet->Scale = GetTransform().GetWorldScale();

			ServerInitManager::Net->SendPacket(Packet);
		}
		// 걸린다면


	}
}

