#include "PreCompile.h"
#include "Sink.h"
#include "Equipment_Plate.h"
Sink::Sink()
{
}

Sink::~Sink()
{
}

void Sink::SetSinkMesh(SinkType _Type)
{
	switch (_Type)
	{
	case SinkType::Normal:
		GetFBXMesh()->SetFBXMesh("m_sk_sink_01.fbx", "Texture");
		GetFBXMesh()->GetTransform().SetWorldMove({ -60, 0, 0 });
		break;
	case SinkType::Wizard:
		GetFBXMesh()->SetFBXMesh("m_wizard_sink_01.fbx", "Texture");
		GetFBXMesh()->GetTransform().SetWorldMove({ -60, 70, 0 });
		break;
	default:
		break;
	}

	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

void Sink::Start()
{
	GamePlayStaticObject::Start();

	SetStuff(GetLevel()->CreateActor<Tool_Sink>());

	GetCollisionObject()->GetTransform().SetWorldScale({ 230, 50, 150 });
	GetCollisionObject()->GetTransform().SetWorldMove({ -60, 25, -10 });
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


Input_PickUpOption Tool_Sink::Input_PickUp(std::shared_ptr<GamePlayMoveable> _Object)
{

	if (_Object->GetToolInfoType() == ToolInfo::Plate &&
		std::dynamic_pointer_cast<Equipment_Plate>(_Object)->IsDirty())
	{

		if (GetCurrentMoveable() == nullptr)
		{
			SetCurrentMoveable(_Object);
			return Input_PickUpOption::PickUp;
		}
		else
		{
			return std::dynamic_pointer_cast<Equipment_Plate>(GetCurrentMoveable())->Input_PickUp(_Object);
		}
	}
	return Input_PickUpOption::NoResponse;

}

Input_PickUpOption Tool_Sink::CheckMoveable(std::shared_ptr<GamePlayMoveable> _Object)
{
	if (_Object->GetToolInfoType() == ToolInfo::Plate &&
		std::dynamic_pointer_cast<Equipment_Plate>(_Object)->IsDirty())
	{
		return Input_PickUpOption::PickUp;
	}
	// _Object->버리는 함수 + SetParent;
	return Input_PickUpOption::NoResponse;
}

//Input_UsingOption Tool_Sink::Input_ActionToManual(std::shared_ptr<Player> _Player, float _DeltaTime)
//{
//	if (GetCurrentMoveable() == nullptr)
//	{
//		return Input_UsingOption::NoResponse;
//	}
//	else
//	{
//		GetCurrentMoveable()->PlusCookingTime(_DeltaTime);
//	}
//	return Input_UsingOption::Using;
//}

//void Tool_Sink::Input_Action_End(std::shared_ptr<GamePlayMoveable> _Moveable)
//{
//	std::shared_ptr<Equipment_Plate> Plate = std::dynamic_pointer_cast<Equipment_Plate>(_Moveable);
//	if (ReturnCleanPlate_ == nullptr)
//	{
//		ReturnCleanPlate_ = Plate;
//	}
//
//
//	if (Plate->Pile_Plate_ != nullptr)
//	{
//		SetCurrentMoveable(Plate->Pile_Plate_);
//	}
//	else
//	{
//		
//	}
//	// 옆에 접시 생성
//}