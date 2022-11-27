#include "PreCompile.h"
#include "Equipment_Bowl.h"

Equipment_Bowl::Equipment_Bowl() 
{
}

Equipment_Bowl::~Equipment_Bowl() 
{
}

void Equipment_Bowl::Start()
{
	GamePlayEquipment::Start();
	GamePlayEquipment::SetToolInfoType(ToolInfo::Bowl);

	GetAnimationFBXMesh()->SetFBXMesh("m_cakemixer_Bowl_01.fbx", "TextureAnimation");
	//GetAnimationFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

void Equipment_Bowl::Update(float _DeltaTime)
{
}
