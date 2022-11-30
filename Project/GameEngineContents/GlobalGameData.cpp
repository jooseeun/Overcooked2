#include "PreCompile.h"
#include "GlobalGameData.h"
#include "InGameUIActor.h"

std::string GlobalGameData::CurStage_ = "";

std::map<std::string, StageData> GlobalGameData::AllStageData_;
std::map<FoodType, FoodData> GlobalGameData::AllFoodData_;

ContentsUtility::Timer GlobalGameData::LeftTime_;;

int GlobalGameData::Score_ = 0;

GlobalGameData::GlobalGameData()
{
}

GlobalGameData::~GlobalGameData()
{
}

InitGlobalGameData::InitGlobalGameData()
{
	//스테이지 데이터 Init
	{
		GlobalGameData::AllStageData_.insert(std::make_pair("1-1",
			CreateStageData("1-1", Thema::SushiCity)));
		GlobalGameData::AllStageData_.insert(std::make_pair("1-2",
			CreateStageData("1-2", Thema::SushiCity)));
		GlobalGameData::AllStageData_.insert(std::make_pair("1-3",
			CreateStageData("1-3", Thema::SushiCity)));
		GlobalGameData::AllStageData_.insert(std::make_pair("1-4",
			CreateStageData("1-4", Thema::WizardKitchen)));
		GlobalGameData::AllStageData_.insert(std::make_pair("2-1",
			CreateStageData("2-1", Thema::WizardKitchen)));
	}

	//음식 데이터 Init
	{
		//플레인버거
		{
			FoodType _Type;
			std::vector<IngredientType> _Ingredient;
			std::vector<ToolInfo> _Cookery;

			_Type = FoodType::PlainBurger;
			_Ingredient.push_back(IngredientType::Bread);
			_Ingredient.push_back(IngredientType::Meat);

			_Cookery.push_back(ToolInfo::None);
			_Cookery.push_back(ToolInfo::FryingPan);

			GlobalGameData::AllFoodData_.insert(std::make_pair(_Type,
				CreateFoodData(_Type, _Ingredient, _Cookery, 30.f)));
		}

		//치즈버거
		{
			FoodType _Type;
			std::vector<IngredientType> _Ingredient;
			std::vector<ToolInfo> _Cookery;

			_Type = FoodType::CheeseBurger;
			_Ingredient.push_back(IngredientType::Bread);
			_Ingredient.push_back(IngredientType::Meat);
			_Ingredient.push_back(IngredientType::Cheese);

			_Cookery.push_back(ToolInfo::None);
			_Cookery.push_back(ToolInfo::FryingPan);
			_Cookery.push_back(ToolInfo::None);

			GlobalGameData::AllFoodData_.insert(std::make_pair(_Type,
				CreateFoodData(_Type, _Ingredient, _Cookery, 50.f)));
		}

		//치즈버거양배추토마토
		{
			FoodType _Type;
			std::vector<IngredientType> _Ingredient;
			std::vector<ToolInfo> _Cookery;

			_Type = FoodType::CheeseBurgerLettuceTomato;
			_Ingredient.push_back(IngredientType::Bread);
			_Ingredient.push_back(IngredientType::Lettuce);
			_Ingredient.push_back(IngredientType::Tomato);
			_Ingredient.push_back(IngredientType::Meat);

			_Cookery.push_back(ToolInfo::None);
			_Cookery.push_back(ToolInfo::None);
			_Cookery.push_back(ToolInfo::None);
			_Cookery.push_back(ToolInfo::FryingPan);

			GlobalGameData::AllFoodData_.insert(std::make_pair(_Type,
				CreateFoodData(_Type, _Ingredient, _Cookery, 80.f)));
		}

		//생선사시미
		{
			FoodType _Type;
			std::vector<IngredientType> _Ingredient;
			std::vector<ToolInfo> _Cookery;

			_Type = FoodType::FishSushimi;
			_Ingredient.push_back(IngredientType::Fish);

			_Cookery.push_back(ToolInfo::None);

			GlobalGameData::AllFoodData_.insert(std::make_pair(_Type,
				CreateFoodData(_Type, _Ingredient, _Cookery, 40.f)));
		}
	}
}

StageData InitGlobalGameData::CreateStageData(std::string_view _StageName, Thema _StageThema)
{
	StageData NewData;
	NewData.StageName = _StageName;
	NewData.StageThema = _StageThema;
	return NewData;
}

FoodData InitGlobalGameData::CreateFoodData(FoodType _Type, std::vector<IngredientType>& _Ingredient, std::vector<ToolInfo>& _Cookery, float _WaitingTime)
{
	FoodData NewFoodData;
	NewFoodData.Type = _Type;
	NewFoodData.Ingredient = _Ingredient;
	NewFoodData.Cookery = _Cookery;
	NewFoodData.WaitingTime = _WaitingTime;
	if (_Ingredient.size() != _Cookery.size())
	{
		MsgBoxAssert("Ingredient의 Size와 Cookery의 Size가 다릅니다.");
	}
	return NewFoodData;
}

InitGlobalGameData CreatGlobalGameDataInst = InitGlobalGameData();

std::string UI_Utility::EnumToString(FoodType _Type)
{
	std::string FileName;
	switch (_Type)
	{
	case FoodType::None:
		break;
	case FoodType::FishSushimi:
		FileName = "ui_FishSushimi.png";
		break;
	case FoodType::PrawnSushimi:
		FileName = "ui_PrawnSushimi.png";
		break;
	case FoodType::PlainBurger:
		FileName = "ui_plainburger.png";
		break;
	case FoodType::CheeseBurger:
		FileName = "ui_cheeseburger.png";
		break;
	case FoodType::CheeseBurgerLettuceTomato:
		FileName = "ui_cheeseburgerlettucetomato.png";
		break;
	default:
		break;
	}

	return FileName;
}

std::string UI_Utility::EnumToString(IngredientType _Type)
{
	std::string FileName = "Plus.png";
	switch (_Type)
	{
	case IngredientType::None:
		FileName = "Plus.png";
		break;
	case IngredientType::Tomato:
		FileName = "Tomato_Icon.png";
		break;
	case IngredientType::Onion:
		FileName = "Onion_Icon.png";
		break;
	case IngredientType::Potato:
		FileName = "Potato_Icon.png";
		break;
	case IngredientType::Dough:
		FileName = "Dough_Icon.png";
		break;
	case IngredientType::Seaweed:
		FileName = "Seaweed_Icon.png";
		break;
	case IngredientType::Mushroom:
		FileName = "Mushroom_Icon.png";
		break;
	case IngredientType::Meat:
		FileName = "Meat_Icon.png";
		break;
	case IngredientType::Lettuce:
		FileName = "Lettuce_Icon.png";
		break;
	case IngredientType::Rice:
		FileName = "Rice_Icon.png";
		break;
	case IngredientType::Flour:
		FileName = "Flour_Icon.png";
		break;
	case IngredientType::Bread:
		FileName = "Bun_Icon.png";
		break;
	case IngredientType::Fish:
		FileName = "Fish_Icon.png";
		break;
	case IngredientType::Sausage:
		FileName = "Sausage_Icon.png";
		break;
	case IngredientType::DumplingSkin:
		FileName = "Plus.png";
		break;
	case IngredientType::Egg:
		FileName = "egg_Icon.png";
		break;
	case IngredientType::Chicken:
		FileName = "Chicken_Icon.png";
		break;
	case IngredientType::Burrito:
		FileName = "Tortilla_Icon.png";
		break;
	case IngredientType::Cheese:
		FileName = "Cheese_Icon.png";
		break;
	case IngredientType::Carrot:
		FileName = "Carrot_Icon.png";
		break;
	case IngredientType::Chocolate:
		FileName = "chocolate_Icon.png";
		break;
	case IngredientType::Honey:
		FileName = "honeycomb_Icon.png";
		break;
	case IngredientType::PastaNoodles:
		FileName = "pasta_Icon.png";
		break;
	case IngredientType::Prawn:
		FileName = "prawn_Icon.png";
		break;
	case IngredientType::Cucumber:
		FileName = "Cucumber_Icon.png";
		break;
	default:
		break;
	}

	return FileName;
}