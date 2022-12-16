#include "PreCompile.h"
#include "GamePlayFood.h"
#include "GlobalGameData.h"
#include "Equipment_Plate.h"
#include "FoodHeader.h"

GamePlayFood::GamePlayFood() 
	: Enum_IngredientType_(IngredientType::None)
	, Trim_(false)
	, MeshName_()
	, FoodThumbnail_(nullptr)
	, Platting_(false)
	, CookingType_(CookingType::Default)
	, Function_TrimmingType_(nullptr)
{
}

GamePlayFood::~GamePlayFood() 
{
}

void GamePlayFood::Start()
{
	GamePlayMoveable::Start();
	GamePlayMoveable::SetObjectMoveableType(ObjectMoveableType::Food);
	GamePlayMoveable::SetHoldType(PlayerHoldType::CanThrow);
	//CookingBar_->LinkObject(CastThis<GameEngineActor>(), { 0,25,0 }, &CookingGage_, false);
	
}

void GamePlayFood::SetObjectFoodClass(IngredientType _Class)
{
	if (FoodThumbnail_ == nullptr)
	{
		FoodThumbnail_ = GetLevel()->CreateActor<FoodThumbnail>();
		FoodThumbnail_->LinkObject(CastThis<GameEngineActor>(), { 0, 50, 0 });
	}
	FoodThumbnail_->SetThumbnail(_Class);
	Enum_IngredientType_ = _Class;

	const std::vector<FoodType>& FoodType__ = GlobalGameData::GetCurStageRef().StageRecipe;
	for (size_t i = 0; i < FoodType__.size(); i++)
	{
		const FoodData& Data = GlobalGameData::GetFoodData(FoodType__[i]);

		for (size_t j = 0; j < Data.Ingredient.size(); j++)
		{
			if (Data.Ingredient[j] == GetObjectFoodClass())
			{
				if (!Data.Cookery.empty())
				{
					if (Data.Cookery[j] == ToolInfo::FryingPan)
					{
						SetCookingType(CookingType::Pried);
					}
					else if (Data.Cookery[j] == ToolInfo::Steamer)
					{
						SetCookingType(CookingType::Steam);
					}
					else if (Data.Cookery[j] == ToolInfo::Mixer)
					{
						SetCookingType(CookingType::Mixer);
					}
					else if (Data.Cookery[j] == ToolInfo::Pot)
					{
						SetCookingType(CookingType::Boil);
					}
					else
					{
						SetCookingType(CookingType::Default);
					}
					return;
				}
				else
				{
					if (Data.CommonCookery[0] == ToolInfo::FryingPan)
					{
						SetCookingType(CookingType::Pried);
					}
					else if (Data.CommonCookery[0] == ToolInfo::Steamer)
					{
						SetCookingType(CookingType::Steam);
					}
					else if (Data.CommonCookery[0] == ToolInfo::Mixer)
					{
						SetCookingType(CookingType::Mixer);
					}
					else if (Data.CommonCookery[0] == ToolInfo::Pot)
					{
						SetCookingType(CookingType::Boil);
					}
					else
					{
						SetCookingType(CookingType::Default);
					}
					return;
				}
			}
		}
	}
}

std::shared_ptr<GamePlayFood> GamePlayFood::GetIngredientClass(IngredientType _Type)
{
	std::shared_ptr<GamePlayFood> Moveable = nullptr;
	switch (_Type)
	{
	case IngredientType::Onion:
		break;
	case IngredientType::Potato:
		break;
	case IngredientType::Dough:
		break;
	case IngredientType::Seaweed:
		Moveable = (GEngine::GetCurrentLevel()->CreateActor<Food_Ingredients_Seaweed>());
		break;
	case IngredientType::Mushroom:
		break;
	case IngredientType::Meat:
		Moveable = (GEngine::GetCurrentLevel()->CreateActor<Food_Ingredients_Meat>());
		break;
	case IngredientType::Lettuce:
		Moveable = (GEngine::GetCurrentLevel()->CreateActor<Food_Ingredients_Lettuce>());
		break;
	case IngredientType::Rice:
		Moveable = (GEngine::GetCurrentLevel()->CreateActor<Food_Ingredients_Rice>());
		break;
	case IngredientType::Flour:
		Moveable = (GEngine::GetCurrentLevel()->CreateActor<Food_Ingredients_Flour>());
		break;
	case IngredientType::Bread:
		Moveable = (GEngine::GetCurrentLevel()->CreateActor<Food_Ingredients_Bread>());
		break;
	case IngredientType::Fish:
		Moveable = (GEngine::GetCurrentLevel()->CreateActor<Food_Ingredients_Fish>());
		break;
	case IngredientType::Sausage:
		break;
	case IngredientType::DumplingSkin:
		break;
	case IngredientType::Egg:
		break;
	case IngredientType::Chicken:
		break;
	case IngredientType::Burrito:
		break;
	case IngredientType::Cheese:
		Moveable = (GEngine::GetCurrentLevel()->CreateActor<Food_Ingredients_Cheese>());
		break;
	case IngredientType::Carrot:
		Moveable = (GEngine::GetCurrentLevel()->CreateActor<Food_Ingredients_Carrot>());
		break;
	case IngredientType::Blueberry:
		break;
	case IngredientType::Honey:
		break;
	case IngredientType::PastaNoodles:
		break;
	case IngredientType::Tomato:
		Moveable = (GEngine::GetCurrentLevel()->CreateActor<Food_Ingredients_Tomato>());
		break;
	case IngredientType::Prawn:
		Moveable = (GEngine::GetCurrentLevel()->CreateActor<Food_Ingredients_Prawn>());
		break;
	case IngredientType::Cucumber:
		Moveable = (GEngine::GetCurrentLevel()->CreateActor<Food_Ingredients_Cucumber>());
		break;
	case IngredientType::Orange:
		break;
	case IngredientType::Nuts:
		break;
	case IngredientType::Strawberry:
		break;
	default:
		break;
	}
	return Moveable;
}


HoldDownEnum GamePlayFood::PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable)
{
	if ((*_Moveable) == nullptr)
	{
		(*_Moveable) = CastThis<GamePlayMoveable>();
		return HoldDownEnum::HoldDown;
	}
	else
	{
		if ((*_Moveable)->CastThis<Equipment_Plate>() != nullptr)
		{
			std::shared_ptr<GamePlayMoveable> Food = CastThis<GamePlayMoveable>();
			switch ((*_Moveable)->PickUp(&Food))
			{
			case HoldDownEnum::HoldUp:
				return HoldDownEnum::HoldDown;
				break;
			default:
				break;
			}
		}
		//MsgBoxAssert("예외 처리 예정. 더빠른 처리를 원하면 컨텐츠 담당자를 닥달해주세요")
	}

	return HoldDownEnum::Nothing;
}

bool GamePlayFood::ReadMapFoodData(std::shared_ptr<GamePlayFood> _Food)
{
	const StageData& Data = GlobalGameData::GetCurStageRef();
	FoodData FoodData_;

	for (size_t i = 0; i < Data.StageRecipe.size(); i++)
	{
		FoodData_ = GlobalGameData::GetFoodData(Data.StageRecipe[i]);
		for (size_t j = 0; j < FoodData_.Ingredient.size(); j++)
		{
			if (FoodData_.Ingredient[j] == _Food->GetObjectFoodClass())
			{
				if (_Food->GetPlatting())
				{
					return true;
				}
			}
		}
	}

	return false;
}