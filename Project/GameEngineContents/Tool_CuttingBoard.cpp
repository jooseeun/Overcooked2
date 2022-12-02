#include "PreCompile.h"
#include "Tool_CuttingBoard.h"
#include "GamePlayMoveable.h"
#include "GamePlayFood.h"
#include "Player.h"

Tool_CuttingBoard::Tool_CuttingBoard()
	: Trimming_(false)
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


//bool Tool_CuttingBoard::HoldDown(std::shared_ptr<Player> _Player)
//{
//	if (Trimming_ == false)
//	{
//		return GetCurrentMoveable()->CastThis<GamePlayStuff>()->HoldUp(_Player);
//	}
//	else
//	{
//		return false;
//	}
//}

 UsingDownEnum Tool_CuttingBoard::UsingDown(std::shared_ptr<Player> _Player)
{
	 if (GetCurrentMoveable() == nullptr)
	 {
		 return UsingDownEnum::Nothing;
	 }
	 else
	 {
		 std::shared_ptr<GamePlayFood> Food = GetCurrentMoveable()->CastThis<GamePlayFood>();
		 if (Food != nullptr)
		 {
			 switch (Food->GetObjectFoodClass())
			 {
			 case IngredientType::Seaweed:
			 case IngredientType::Rice:
			 case IngredientType::Flour:
			 case IngredientType::Bread:
			 case IngredientType::DumplingSkin:
			 case IngredientType::Egg:
			 case IngredientType::Burrito:
			 case IngredientType::Honey:
			 case IngredientType::PastaNoodles:
				 break;
			 case IngredientType::Tomato:
			 case IngredientType::Onion:
			 case IngredientType::Potato:
			 case IngredientType::Dough:
			 case IngredientType::Mushroom:
			 case IngredientType::Meat:
			 case IngredientType::Lettuce:
			 case IngredientType::Fish:
			 case IngredientType::Sausage:
			 case IngredientType::Chicken:
			 case IngredientType::Cheese:
			 case IngredientType::Carrot:
			 case IngredientType::Chocolate:
			 case IngredientType::Prawn:
			 case IngredientType::Cucumber:
				 if (Food->Input_Manual(_Player, 5.f, GameEngineTime::GetDeltaTime())) // 원래 12초
				 {
					 return UsingDownEnum::Nothing;
				 }
				 return UsingDownEnum::Using;
				 break;
			 default:
				 MsgBoxAssert("아직 설정되지 않은 재료")
				 break;
			 }

		
		 }
	 }
	return UsingDownEnum::Nothing;
};

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