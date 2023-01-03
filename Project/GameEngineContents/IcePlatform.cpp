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

	//if (IsFirst_ == true) // Lerp ���
	//{
	//	float Z = GetTransform().GetWorldPosition().z;
	//	IsFirst_ = false;
	//}
	if ((ServerInitManager::Net == nullptr || ServerInitManager::Net->GetIsHost())) // ȣ��Ʈ�̰ų� �ַ��÷��̴���
	{
		if (GetTransform().GetWorldPosition().z > 1329.f)
		{
			GetTransform().SetWorldPosition({ -1984.f, -100.f, -2722.f });
		}
		else
		{

			GetTransform().SetWorldMove({ MoveDir_ * _DeltaTime });
		}


		// ��Ʈ��ũ�� �Ȱɸ��ٸ�
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
		// �ɸ��ٸ�


	}
}

