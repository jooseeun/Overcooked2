#include "PreCompile.h"
#include "Equipment_Pot.h"

Equipment_Pot::Equipment_Pot() 
{
}

Equipment_Pot::~Equipment_Pot() 
{
}

void Equipment_Pot::Start()
{
	GamePlayBowl::Start();
	GamePlayBowl::SetToolInfoType(ToolInfo::Pot);

	GetFBXMesh()->SetFBXMesh("m_sk_pot_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}
