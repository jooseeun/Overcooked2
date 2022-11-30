#include "PreCompile.h"
#include "Portal.h"

Portal::Portal() 
{
}

Portal::~Portal() 
{
}

void Portal::SetPortalType(PortalType _PortalType)
{
	switch (_PortalType)
	{
	case PortalType::Blue: 
	{
		GetAnimationFBXMesh()->SetFBXMesh("Portal_Blue.fbx");
	}
		break;
	case PortalType::Purple:
	{
		GetAnimationFBXMesh()->SetFBXMesh("Portal_Purple.fbx");
	}
		break;
	default:
		break;
	}
}

void Portal::Start()
{
	GamePlayMapObject::Start();
	GetCollisionObject()->GetTransform().SetLocalPosition({ 100, 100, 100 });
}

void Portal::Update(float _DeltaTime)
{
}

