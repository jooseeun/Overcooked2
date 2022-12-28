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
	GetCollisionObject()->GetTransform().SetWorldMove({ -30.f, 0.f, 0.f });

	std::shared_ptr<GameEngineCollision> PlusCol = CreateComponent<GameEngineCollision>();
	PlusCol->GetTransform().SetLocalScale({ 180.00,200.00,514.00 });
	PlusCol->GetTransform().SetLocalPosition(GetTransform().GetWorldPosition() + float4{ -15,100,0 });
	PlusCol->ChangeOrder(CollisionOrder::Map_IcePlatform);
}

void IcePlatform::Update(float _DeltaTime)
{
	if (GetTransform().GetWorldPosition().z > 1329.f)
	{
		GetTransform().SetWorldPosition({ -1984.f, -100.f, -2722.f });
	}
	else
	{
		GetTransform().SetWorldMove({ MoveDir_ * _DeltaTime });
	}

}

