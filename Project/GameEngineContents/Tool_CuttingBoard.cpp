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

}

Input_PickUpOption Tool_CuttingBoard::CheckMoveable(GamePlayMoveable* _Object)
{
	switch (_Object->GetObjectMoveableType())
	{
	case ObjectMoveableType::Food:
		{
			GamePlayFood* Food = dynamic_cast<GamePlayFood*>(_Object);
			switch (Food->GetObjectFoodClass())
			{
			case ObjectFoodClass::Fish:
			case ObjectFoodClass::Shrimp:
				return Input_PickUpOption::PickUp;
				break;
			default:
				MsgBoxAssert("분기 업데이트 해야합니다")
					break;
			}
		}
		break;
	default:
		break;
	}
	return Input_PickUpOption::NoResponse;
}