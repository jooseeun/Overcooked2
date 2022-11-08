#include "PreCompile.h"
#include "Sink.h"
#include "Equipment_Plate.h"
Sink::Sink() 
{
}

Sink::~Sink() 
{
}

void Sink::Start()
{
	GamePlayStaticObject::Start();

	SetStuff(GetLevel()->CreateActor<Tool_Sink>());
}



// ----------------------Tool---------------------------
Tool_Sink::Tool_Sink()
{
}

Tool_Sink::~Tool_Sink()
{
}

void Tool_Sink::Start()
{
	GamePlayTool::Start();
	GamePlayTool::SetInteractOption(Input_InteractOption::Manual);
	GamePlayTool::SetToolInfoType(ToolInfo::Cooker);

}

Input_PickUpOption Tool_Sink::CheckMoveable(GamePlayMoveable* _Object)
{
	if (_Object->GetToolInfoType() == ToolInfo::Plate &&
		dynamic_cast<Equipment_Plate*>(_Object)->IsDirty())
	{
		return Input_PickUpOption::PickUp;
	}
	// _Object->버리는 함수 + SetParent;
	return Input_PickUpOption::NoResponse;
}

Input_InteractOption Tool_Sink::Input_Action()
{
	return Input_InteractOption::NoResponse;
}