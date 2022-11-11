#include "PreCompile.h"
#include "Tool_CuttingBoard.h"
#include "GamePlayMoveable.h"
#include "GamePlayFood.h"

Tool_CuttingBoard::Tool_CuttingBoard()
{
}

Tool_CuttingBoard::~Tool_CuttingBoard()
{
}

void Tool_CuttingBoard::Start()
{
	GamePlayTool::Start();
	GamePlayTool::SetInteractOption(AutoOption::Manual);
	GamePlayTool::SetToolInfoType(ToolInfo::CuttingBoard);
	SetCookingEndTime(7.f);	

	GetFBXMesh()->SetFBXMesh("CuttingBoard.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

//Input_PickUpOption Tool_CuttingBoard::CheckMoveable(GamePlayMoveable* _Object)
//{
//	switch (_Object->GetObjectMoveableType())
//	{
//	case ObjectMoveableType::Food:
//	{
//		GamePlayFood* Food = dynamic_cast<GamePlayFood*>(_Object);
//		switch (Food->GetObjectFoodClass())
//		{
//		case ObjectFoodClass::Fish:
//		case ObjectFoodClass::Prawn:
//			return Input_PickUpOption::PickUp;
//			break;
//		default:
//			MsgBoxAssert("분기 업데이트 해야합니다")
//				break;
//		}
//	}
//	break;
//	default:
//		break;
//	}
//	return Input_PickUpOption::NoResponse;
//}

//Input_InteractOption Tool_CuttingBoard::Input_Interact()
//{
//
//}

