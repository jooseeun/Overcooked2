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
	//GamePlayTool::SetToolInfoType(ToolInfo::Cooker);

}

Input_PickUpOption Tool_Cooker::CheckMoveable(GamePlayMoveable* _Object)
{
	GamePlayBowl* Bowl = dynamic_cast<GamePlayBowl*>(_Object);
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