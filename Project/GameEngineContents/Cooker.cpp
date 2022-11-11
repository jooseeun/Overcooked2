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
	SetCookingEndTime(12.f);
	//GamePlayTool::SetToolInfoType(ToolInfo::Cooker);
}

Input_PickUpOption Tool_Cooker::CheckMoveable(std::shared_ptr<GamePlayMoveable> _Object)
{
	std::shared_ptr<GamePlayBowl> Bowl = std::dynamic_pointer_cast<GamePlayBowl>(_Object);
	if (Bowl != nullptr)
	{
		switch (Bowl->GetToolInfoType())
		{
		case ToolInfo::FryingPan:
		case ToolInfo::Pot:
			return Input_PickUpOption::PickUp;
			break;
		default:
			return Input_PickUpOption::NoResponse;
			break;
		}

	}
	else
	{
		return Input_PickUpOption::NoResponse;
	}
}