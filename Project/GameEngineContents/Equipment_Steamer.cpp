#include "PreCompile.h"
#include "Equipment_Steamer.h"

Equipment_Steamer::Equipment_Steamer() 
{
}

Equipment_Steamer::~Equipment_Steamer() 
{
}

void Equipment_Steamer::Start()
{
	GamePlayEquipment::Start();
	GamePlayEquipment::SetToolInfoType(ToolInfo::Steamer);

	GetFBXMesh()->SetFBXMesh("m_steamer_Body.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 1.5, 1.5, 1.5 });
	GetCollisionObject()->GetTransform().SetWorldPosition({ 0, -25, 0 });
	GetCollisionObject()->GetTransform().SetLocalScale({ GetFBXMesh()->GetTransform().GetWorldScale().x / 2 , GetFBXMesh()->GetTransform().GetWorldScale().y / 2, GetFBXMesh()->GetTransform().GetWorldScale().z / 2});
}

void Equipment_Steamer::Update(float _DeltaTime)
{
}
