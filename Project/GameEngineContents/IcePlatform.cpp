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

	GetFBXMesh()->SetFBXMesh("m_dlc09_iceplatform_0.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	GetFBXMesh()->GetTransform().SetWorldMove({ 0, 0, 0 });

	GetCollisionObject()->GetTransform().SetWorldScale({100, 100, 100});
}

