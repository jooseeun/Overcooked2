#include "PreCompile.h"
#include "Cooker.h"
#include "GamePlayBowl.h"

Cooker::Cooker() 
{
}

Cooker::~Cooker() 
{
}

void Cooker::Start()
{
	GamePlayStaticObject::Start();

	GetCollisionObject()->GetTransform().SetWorldScale({ 230, 50, 150 });
	GetCollisionObject()->GetTransform().SetWorldMove({ -60, 25, -10 });

	GetFBXMesh()->SetFBXMesh("m_sk_cooker_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	GetFBXMesh()->GetTransform().SetWorldMove({ 0, 0, 0 });
}


// ----------------------Tool---------------------------

Tool_Cooker::Tool_Cooker()
{
}

Tool_Cooker::~Tool_Cooker()
{
}


void Tool_Cooker::Start()
{
	GamePlayTool::Start();
	GamePlayTool::SetInteractOption(AutoOption::Auto);
	//SetCookingEndTime(12.f);
	GamePlayTool::SetObjectToolType(ObjectToolType::Cooker);
}

//HoldDownEnum Tool_Cooker::HoldDown(std::shared_ptr<GamePlayStuff> _Stuff)
//{
//	//if (std::dynamic_pointer_cast<>)
//	//{
//
//	//}
//}