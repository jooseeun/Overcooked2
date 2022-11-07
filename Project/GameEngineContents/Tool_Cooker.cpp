#include "PreCompile.h"
#include "Tool_Cooker.h"
#include "GamePlayBowl.h"

Tool_Cooker::Tool_Cooker() 
{
}

Tool_Cooker::~Tool_Cooker() 
{
}


void Tool_Cooker::Start()
{
	GamePlayTool::Start();
	GamePlayTool::SetInteractOption(Input_InteractOption::Auto);
	GamePlayTool::SetToolInfoType(ToolInfo::Cooker);

}

Input_PickUpOption Tool_Cooker::CheckMoveable(GamePlayMoveable* _Object)
{
	GamePlayBowl* Bowl = dynamic_cast<GamePlayBowl*>(_Object);
	if (Bowl != nullptr)
	{
		switch (Bowl->GetToolInfoType())
		{
		case ToolInfo::FryingPan :
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