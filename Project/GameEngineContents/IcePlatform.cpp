#include "PreCompile.h"
#include "IcePlatform.h"

IcePlatform::IcePlatform() 
{
}

IcePlatform::~IcePlatform()
{
}

void IcePlatform::Start()
{
	GamePlayFloor::Start();

	GetFBXMesh()->SetFBXMesh("m_dlc09_iceplatform_3.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });

	GetCollisionObject()->GetTransform().SetWorldScale({257.f, 200.f, 514.f});
	GetCollisionObject()->GetTransform().SetWorldMove({ -30.f, 0.f, 0.f });
}

void IcePlatform::Update(float _DeltaTime)
{
}

