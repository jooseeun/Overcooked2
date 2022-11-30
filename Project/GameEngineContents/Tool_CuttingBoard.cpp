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
	GamePlayTool::SetObjectToolType(ObjectToolType::CuttingBoard);

	// 칼
	Knife_ = GetLevel()->CreateActor<GameEngineActor>();
	Knife_->SetParent(shared_from_this());

	std::shared_ptr<GameEngineFBXStaticRenderer> KnifeRenderer = Knife_->CreateComponent<GameEngineFBXStaticRenderer>();
	KnifeRenderer->SetFBXMesh("CuttingBoard.fbx", "Texture", 0);
	KnifeRenderer->GetTransform().SetWorldScale({ 100, 100, 100 });

	// 도마
	GetFBXMesh()->SetFBXMesh("CuttingBoard.fbx", "Texture", 1);
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

UsingDownEnum Tool_CuttingBoard::UsingDown(std::shared_ptr<Player> _Player)
{
	return UsingDownEnum::Nothing;
}

bool Tool_CuttingBoard::CanHoldThis(std::shared_ptr<GamePlayMoveable> _Moveable)
{
	return true;
}

//
//HoldDownEnum Tool_CuttingBoard::HoldDown(std::shared_ptr<Player> _Player)
//{
//	std::weak_ptr<GamePlayMoveable> Moveable = std::dynamic_pointer_cast<GamePlayMoveable>(_Player->GetPlayerHolding());
//
//	if (GetCurrentMoveable() == nullptr)
//	{
//		if (Moveable.lock() != nullptr && CanHoldThis(Moveable.lock()))
//		{
//			SetMoveable(_Player);
//			return HoldDownEnum::HoldDown_Already;
//		}
//		elseㅔ
//		{
//			return HoldDownEnum::Nothing;
//		}
//	}
//	else
//	{
//		switch (GetCurrentMoveable()->HoldDown(_Player))
//		{
//		case HoldDownEnum::Nothing:
//			return HoldDownEnum::Nothing;
//			break;
//		case HoldDownEnum::HoldDown:
//			MsgBoxAssert("오류 확인")
//		case HoldDownEnum::HoldDown_Already:
//			return HoldDownEnum::HoldDown_Already;
//			break;
//		case HoldDownEnum::HoldUp:
//			MsgBoxAssert("오류 확인")
//		case HoldDownEnum::HoldUp_Already:
//			break;
//		default:
//			break;
//		}
//	}
//	
//	if (Moveable.lock() == nullptr)
//	{
//		if (GetCurrentMoveable() == nullptr)
//		{
//			return HoldDownEnum::Nothing;
//		}
//		else
//		{
//			_Player->SetPlayerHolding(GetCurrentMoveable());
//			ReSetCurrentMoveable();
//			return HoldDownEnum::HoldUp_Already;
//		}
//	}
//	else
//	{
//		if (GetCurrentMoveable() == nullptr && CanHoldThis(Moveable.lock()))
//		{
//			SetMoveable(_Player);
//			return HoldDownEnum::HoldDown_Already;
//		}
//		else
//		{
//			//if (SetMoveable())
//			//{
//
//			//}
//			switch (GetCurrentMoveable()->HoldDown(_Player))
//			{
//			case HoldDownEnum::Nothing:
//				return HoldDownEnum::Nothing;
//				break;
//			case HoldDownEnum::HoldDown:
//				MsgBoxAssert("예외처리 대기중")
//			case HoldDownEnum::HoldDown_Already:
//				return HoldDownEnum::HoldDown_Already;
//				break;
//			case HoldDownEnum::HoldUp:
//				MsgBoxAssert("예외처리 대기중")
//			case HoldDownEnum::HoldUp_Already:
//				return HoldDownEnum::HoldUp_Already;
//				break;
//			default:
//				break;
//			}
//		}
//	}
//	return HoldDownEnum::Nothing;
//}