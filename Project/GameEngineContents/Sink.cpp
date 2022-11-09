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
	GamePlayTool::SetInteractOption(AutoOption::Manual);
	SetCookingEndTime(4.f);
	//GamePlayTool::SetToolInfoType(ToolInfo::Cooker);

}


Input_PickUpOption Tool_Sink::Input_PickUp(GamePlayMoveable* _Object)
{

	if (_Object->GetToolInfoType() == ToolInfo::Plate &&
		dynamic_cast<Equipment_Plate*>(_Object)->IsDirty())
	{

		if (GetCurrentMoveable() == nullptr)
		{
			SetCurrentMoveable(_Object);
		}
		else
		{
			dynamic_cast<Equipment_Plate*>(GetCurrentMoveable())->PlusPlateStack();
			_Object->Death();
		}

		return Input_PickUpOption::PickUp;

	}
	return Input_PickUpOption::NoResponse;

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

Input_UsingOption Tool_Sink::Input_ActionToManual(Player* _Player, float _DeltaTime)
{
	if (GetCurrentMoveable() == nullptr)
	{
		return Input_UsingOption::NoResponse;
	}
	else
	{
		GetCurrentMoveable()->PlusCookingTime(_DeltaTime);
	}
	return Input_UsingOption::Using;
}

void Tool_Sink::Input_Action_End(GamePlayMoveable* _Moveable)
{
	Equipment_Plate* Plate = dynamic_cast<Equipment_Plate*>(_Moveable);
	if (Plate->GetPlateStack() > 1)
	{
		Plate->MinusPlateStack();


		//GetLevel()->CreateActor<Equipment_Plate>();
	

	}
	else
	{
		//SetCurrentMoveable(nullptr)
	}
	// 옆에 접시 생성
}