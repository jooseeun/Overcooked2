#include "PreCompile.h"
#include "GamePlayFood.h"
#include "GlobalGameData.h"

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
					else
					{
						SetCookingType(CookingType::Default);
					}
				}
				else
				{
					SetCookingType(CookingType::Default);
				}


			}
		}
	}
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
		MsgBoxAssert("예외 처리 예정. 더빠른 처리를 원하면 컨텐츠 담당자를 닥달해주세요")
	}

	return HoldDownEnum::Nothing;
}
