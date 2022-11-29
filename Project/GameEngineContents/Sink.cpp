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
	GamePlayTool::SetObjectToolType(ObjectToolType::Sink);

}

//Input_PutDownOption Tool_Sink::Input_PutDown(std::shared_ptr<GamePlayMoveable> _Object)
//{
//
//	//if (_Object->GetToolInfoType() == ToolInfo::Plate &&
//	//	std::dynamic_pointer_cast<Equipment_Plate>(_Object)->IsDirty())
//	//{
//
//	//	if (GetCurrentMoveable() == nullptr)
//	//	{
//	//		SetCurrentMoveable(_Object);
//	//		return Input_PutDownOption::PickUp;
//	//	}
//	//	else
//	//	{
//	//		return std::dynamic_pointer_cast<Equipment_Plate>(GetCurrentMoveable())->Input_PickUp(_Object);
//	//	}
//	//}
//	//return Input_PutDownOption::NoResponse;
//
//}
