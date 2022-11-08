#include "PreCompile.h"
#include "TrashCan.h"

TrashCan::TrashCan() 
{
}

TrashCan::~TrashCan() 
{
}

void TrashCan::Start()
{
	GamePlayStaticObject::Start();

	GetCollisionObject()->GetTransform().SetWorldScale({ 100, 50, 100 });
	GetCollisionObject()->GetTransform().SetWorldMove({ 0, 25, 0 });

	GetFBXMesh()->SetFBXMesh("m_sk_bin_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });

	SetStuff(GetLevel()->CreateActor<Tool_TrashCan>());
}

// ----------------------Tool---------------------------

Tool_TrashCan::Tool_TrashCan()
{
}

Tool_TrashCan::~Tool_TrashCan()
{
}

void Tool_TrashCan::Start()
{
	GamePlayTool::Start();
	GamePlayTool::SetInteractOption(AutoOption::Manual);
	//GamePlayTool::SetToolInfoType(ToolInfo::TrashCan);
}

Input_PickUpOption Tool_TrashCan::CheckMoveable(GamePlayMoveable* _Object)
{
	// _Object->������ �Լ� + SetParent;
	return Input_PickUpOption::NoResponse;
}
//
//Input_AutoOption Tool_TrashCan::Input_Action()
//{
//	return Input_AutoOption::NoResponse;
//}