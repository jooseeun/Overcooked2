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
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

void Equipment_Steamer::Update(float _DeltaTime)
{
}
