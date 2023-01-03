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
		GetFBXMesh()->SetSubMaterial(2, "Swirl");
		std::vector<std::vector<std::shared_ptr<GameEngineRenderUnit>>>& Unit = GetFBXMesh()->GetAllRenderUnit();
		Unit[2][0]->ShaderResources.SetTexture("Tex", "t_pfx_portal_d.png");
		//BlendRenderer_->SetFBXMesh("Portal_Blue2.fbx", "Texture", 1);
	}
		break;
	case MapObjType::Portal_Purple:
	{
		GetFBXMesh()->SetFBXMesh("Portal_Purple2.fbx", "Texture");
		GetFBXMesh()->SetSubMaterial(2, "Swirl");
		std::vector<std::vector<std::shared_ptr<GameEngineRenderUnit>>>& Unit = GetFBXMesh()->GetAllRenderUnit();
		Unit[2][0]->ShaderResources.SetTexture("Tex", "t_pfx_portal_2_d.png");
		//BlendRenderer_->SetFBXMesh("Portal_Purple2.fbx", "Texture", 1);
	}
		break;
	default:
		break;
	}
	//GetFBXMesh()->GetFBXMesh()-> GetFbxRenderUnit()[1].MaterialData[0].DifTexturePath = NewPath;

	GetFBXMesh()->SetSubMaterial(1, "Portal");


	//GetFBXMesh()->SEtTe
	//GetFBXMesh()->GetAllRenderUnit()[0][0].GetMesh()->Set
	//GetFBXMesh()->SetSubMaterial(2, "Swirl");
	GetFBXMesh()->SetSubConstantBufferLink(2, "RENDEROPTION", &RenderOptionSwirl, sizeof(RenderOption));

	GetFBXMesh()->SetSubConstantBufferLink(1, "RENDEROPTION", &RenderOptionMyInst, sizeof(RenderOption));
}

void Portal::Start()
{
	GamePlayMapObject::Start();
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	GetCollisionObject()->Off();
	//GetCollisionObject()->GetTransform().SetLocalScale({ 100, 100, 100 });
	//GetCollisionObject()->GetTransform().SetLocalMove({ 0, 100, 0 });
	
	GetFBXMesh()->GetTransform().SetAddWorldRotation({ 90, 0, 0 });
}

void Portal::Update(float _DeltaTime)
{
	GamePlayObject::Update(_DeltaTime);
	RenderOptionMyInst.UV.y += _DeltaTime * 1.7f;
	RenderOptionSwirl.Random += 5.f;

}

