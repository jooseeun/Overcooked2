#include "PreCompile.h"
#include "Equipment_Plate.h"
#include "GlobalGameData.h"

Equipment_Plate::Equipment_Plate()
	: Dirty_(false)
	, Pile_Plate_(nullptr)
	, Washing_(false)
{
}

Equipment_Plate::~Equipment_Plate() 
{
}

void Equipment_Plate::Start()
{
	GamePlayBowl::Start();
	GamePlayBowl::SetToolInfoType(ToolInfo::Plate);

	GetFBXMesh()->SetFBXMesh("m_sk_plate_02.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	GetCollisionObject()->GetTransform().SetWorldPosition({ 0, -25, 0});
	GetCollisionObject()->GetTransform().SetLocalScale({ 100, 25, 100 });


	GetCombinFood()->Start(1, shared_from_this(), false);
}

void Equipment_Plate::SetDirty()
{
	Dirty_ = true;
	// 텍스쳐 변경필요
}

void Equipment_Plate::SetClean()
{
	Dirty_ = false;
	// 텍스쳐 변경필요
}

HoldDownEnum Equipment_Plate::PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable)
{
	if ((*_Moveable) != nullptr)
	{
		std::weak_ptr<GamePlayFood> Food = (*_Moveable)->CastThis<GamePlayFood>();
		if (Food.lock() != nullptr)
		{
			const StageData& Data = GlobalGameData::GetCurStageRef();
			FoodData FoodData_;

			for (size_t i = 0; i < Data.StageRecipe.size(); i++)
			{
				FoodData_ = GlobalGameData::GetFoodData(Data.StageRecipe[i]);
				for (size_t j = 0; j < FoodData_.Ingredient.size(); j++)
				{
					if (FoodData_.Ingredient[j] == Food.lock()->GetObjectFoodClass())
					{
						if (Food.lock()->GetPlatting())
						{

							if (GetCombinFood()->IsClear())
							{
								GetCombinFood()->PushFood(Food.lock()->GetObjectFoodClass());
								GetCombinFood()->SetRenderer(*_Moveable);

								(*_Moveable)->Death();
								(*_Moveable)->Off();
								(*_Moveable) = nullptr;

								return HoldDownEnum::HoldUp;
							}
							
						}
					}
				}
			}
		}
		else
		{

		}
	}
	else
	{
		(*_Moveable) = CastThis<GamePlayMoveable>();
		return HoldDownEnum::HoldDown;
	}
	return HoldDownEnum::Nothing;
}

//HoldDownEnum Equipment_Plate::HoldOn(std::shared_ptr<Player> _Player) 
//{
//	if (_Player->GetPlayerHolding() == nullptr)
//	{
//		_Player->SetPlayerHolding(shared_from_this());
//		return HoldDownEnum::HoldUp;
//	}
//	else
//	{
//		if (_Player->GetPlayerHolding()->CastThis<GamePlayFood>() != nullptr)
//		{
//			IngredientType Type = _Player->GetPlayerHolding()->CastThis<GamePlayFood>()->GetObjectFoodClass();
//			for (size_t i = 0; i < GetCombinFood()->Food_Current_.size(); i++)
//			{
//				if (GetCombinFood()->Food_Current_[i] == IngredientType::None)
//				{
//					continue;
//				}
//				else if(GamePlayFood::CheckCombine(GetCombinFood()->Food_Current_[i], Type) == ReturnMix::NoMix)
//				{
//					return HoldDownEnum::Nothing;
//				}
//			}
//			if (!GetCombinFood()->PushFood(Type))
//			{
//				return HoldDownEnum::Nothing;
//			}
//			_Player->DetachPlayerHolding();
//			return HoldDownEnum::HoldDown;
//		}
//		else if (_Player->GetPlayerHolding()->CastThis<GamePlayBowl>() != nullptr)
//		{
//			MsgBoxAssert("아직")
//		}
//		else
//		{
//			return HoldDownEnum::Nothing;
//		}
//		return HoldDownEnum::Nothing;
//	}
//}
//
//HoldDownEnum Equipment_Plate::PickUp(std::shared_ptr<GamePlayMoveable> _Moveable)
//{

//
//	return HoldDownEnum::Nothing;
//}
//


//Input_PutDownOption Equipment_Plate::Input_PutDown(std::shared_ptr<GamePlayMoveable> _Object)
//{
//	if (Dirty_ == true)
//	{
//		if (_Object->GetToolInfoType() == ToolInfo::Plate &&
//			std::dynamic_pointer_cast<Equipment_Plate>(_Object)->IsDirty())
//		{
//			std::shared_ptr<Equipment_Plate> Pile_Plate_Before = nullptr; // 방어코드
//			std::shared_ptr<Equipment_Plate> Pile_Plate = std::dynamic_pointer_cast<Equipment_Plate>(shared_from_this());
//
//			int Stack = 0;
//			while (true)
//			{
//				if (Stack > 10)
//				{
//					MsgBoxAssert("무한 루프입니다")
//				}
//				if (Pile_Plate->Pile_Plate_ != nullptr)
//				{
//					Pile_Plate_Before = Pile_Plate;
//					Pile_Plate = Pile_Plate->Pile_Plate_;
//					if (Pile_Plate_Before == Pile_Plate)
//					{ 
//						MsgBoxAssert("무한 루프입니다")
//					}
//
//				}
//				else
//				{
//					Pile_Plate->Pile_Plate_ = std::dynamic_pointer_cast<Equipment_Plate>(_Object);
//					return Input_PutDownOption::PutDown;
//					break;
//				}
//				Stack++;
//			}
//		}
//	}
//	else
//	{
//		// 음식 조합
//	}
//
//	return Input_PutDownOption::NoResponse; // 수정요
//}
//
//Input_PickUpOption Equipment_Plate::Input_PickUp(std::shared_ptr<Player> _Player)
//{
//	if (Washing_ == true)
//	{
//		return Input_PickUpOption::NoResponse;
//	}
//	return Input_PickUpOption::PickUp;
//}

