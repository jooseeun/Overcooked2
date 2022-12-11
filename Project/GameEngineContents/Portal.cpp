#include "PreCompile.h"
#include "Portal.h"

Portal::Portal() 
{
}

Portal::~Portal() 
{
}

void Portal::SetPortalMesh(MapObjType _PortalType)
{
	switch (_PortalType)
	{
	case MapObjType::Portal_Blue:
	{
		GetFBXMesh()->SetFBXMesh("Portal_Blue2.fbx", "Texture");
		//BlendRenderer_->SetFBXMesh("Portal_Blue2.fbx", "Texture", 1);
	}
		break;
	case MapObjType::Portal_Purple:
	{
		GetFBXMesh()->SetFBXMesh("Portal_Purple2.fbx", "Texture");
		//BlendRenderer_->SetFBXMesh("Portal_Purple2.fbx", "Texture", 1);
	}
		break;
	default:
		break;
	}

	GetFBXMesh()->SetSubMaterial(1, "Portal");
	GetFBXMesh()->SetSubConstantBufferLink(1, "RENDEROPTION", &RenderOptionMyInst, sizeof(RenderOption));
}

void Portal::Start()
{
	GamePlayMapObject::Start();
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	//GetCollisionObject()->GetTransform().SetLocalScale({ 100, 100, 100 });
	//GetCollisionObject()->GetTransform().SetLocalMove({ 0, 100, 0 });
	
	GetFBXMesh()->GetTransform().SetAddWorldRotation({ 90, 0, 0 });
}

void Portal::Update(float _DeltaTime)
{
	RenderOptionMyInst.UV.y += _DeltaTime * 1.7f;
}

