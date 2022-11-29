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

	GetFBXMesh()->SetFBXMesh("Bowl_Static.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 1, 1, 1 });

	//GetAnimationFBXMesh()->SetFBXMesh("m_cakemixer_Bowl_01.fbx", "TextureAnimation");
	//GetAnimationFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });

	//GameEngineRenderingEvent Event;
	//Event.ResourcesName = "m_cakemixer_Bowl_01.FBX";
	//Event.Loop = true;
	//Event.Inter = 0.1f;
	//GetAnimationFBXMesh()->CreateFBXAnimation("Idle", Event, 1);

	//GetAnimationFBXMesh()->ChangeAnimation("Idle");
}

void Equipment_Bowl::Update(float _DeltaTime)
{
}
