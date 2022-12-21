#include "PreCompile.h"
#include "GamePlayBowl.h"
#include "GamePlayFood.h"

std::map<NoneFoodType, std::vector<IngredientType>> CombinFood::Static_NoneType_;

GamePlayBowl::GamePlayBowl() 
	: Enum_ObjectBowlType_(ObjectBowlType::None)
	, CombinFood_(nullptr)
{
}

GamePlayBowl::~GamePlayBowl() 
{	
}

void GamePlayBowl::Start()
{
	GamePlayEquipment::Start();
	GamePlayEquipment::SetObjectEquipmentType(ObjectEquipmentType::Bowl);

	//{
	//	const StageData& StageData_ = GlobalGameData::GetCurStageRef();
	//	std::vector<IngredientType> Data;
	//	for (size_t i = 0; i < StageData_.StageRecipe.size(); i++)
	//	{
	//		Data = GlobalGameData::GetFoodData(StageData_.StageRecipe[i]).Ingredient;
	//		std::vector<IngredientType> Food_Current = Food_Current_;
	//		bool IsThat = false;
	//		int Index = 0;
	//		for (size_t j = 0; j < Data.size(); j++)
	//		{
	//			IsThat = false;
	//			for (size_t k = 0; k < Food_Current.size(); k++)
	//			{
	//				if (Food_Current[k] == IngredientType::None)
	//				{
	//					continue;
	//				}
	//				if (Data[j] == Food_Current[k])
	//				{
	//					Index++;
	//					IsThat = true;
	//					Data[j] = IngredientType::None;
	//					Food_Current[k] = IngredientType::None;
	//					break;
	//				}
	//			}

	//			if (IsThat == false)
	//			{
	//				break;
	//			}
	//		}

	//		if (Index == Data.size() && IsThat == true)
	//		{
	//			return StageData_.StageRecipe[i];
	//		}
	//	}
	//}

}


//
//HoldDownEnum GamePlayBowl::HoldOn(std::shared_ptr<Player> _Player)
//{
//	if (_Player->GetPlayerHolding() == nullptr)
//	{
//		_Player->SetPlayerHolding(shared_from_this());
//		return HoldDownEnum::HoldUp;
//	}
//	else
//	{
//		if (_Player->GetPlayerHolding()->CastThis<GamePlayMoveable>()->GetObjectMoveableType() == ObjectMoveableType::Equipment)
//		{
//			if (_Player->GetPlayerHolding()->CastThis<GamePlayEquipment>()->GetObjectEquipmentType() == ObjectEquipmentType::Using)
//			{
//				return HoldDownEnum::Nothing;
//			}
//			else
//			{
//				if (_Player->GetPlayerHolding()->CastThis<GamePlayBowl>()->GetObjectBowlType() == ObjectBowlType::)
//				{
//
//				}
//				return HoldDownEnum::Nothing;
//			}
//		}
//		else
//		{
//			switch (GamePlayFood::CheckCombine(_Player->GetPlayerHolding()->CastThis<GamePlayFood>()->GetObjectFoodClass(), ))
//			{
//			case ReturnMix::NoMix:
//				break;
//			case ReturnMix::AtoB:
//				break;
//			case ReturnMix::BtoA:
//				break;
//			default:
//				break;
//			}
//		}
//		return HoldDownEnum::Nothing;
//	}
//};