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
	GamePlayTool::SetInteractOption(AutoOption::Auto);
	SetCookingEndTime(1.f);
	//GamePlayTool::SetToolInfoType(ToolInfo::TrashCan);
}

void Tool_TrashCan::Input_ActionToAuto_Update(std::shared_ptr<GamePlayMoveable> _Moveable, float _DeltaTime)
{
	_Moveable->PlusCookingTime(_DeltaTime);
	// 돌면서 작아지는 기능
}

void Tool_TrashCan::Input_Action_End(std::shared_ptr<GamePlayMoveable> _Moveable)
{
	_Moveable->Death();// 삭제한다
	ReSetCurrentMoveable();
}


Input_PickUpOption Tool_TrashCan::CheckMoveable(std::shared_ptr<GamePlayMoveable> _Object)
{
	return Input_PickUpOption::PickUp;
}

Input_PickUpOption Tool_TrashCan::Input_PickUp(std::shared_ptr<Player> _Player)
{
	return Input_PickUpOption::NoResponse;
}
//
//Input_AutoOption Tool_TrashCan::Input_Action()
//{
//	return Input_AutoOption::NoResponse;
//}