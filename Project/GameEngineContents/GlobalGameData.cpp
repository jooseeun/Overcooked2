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
	//�������� ������ Init
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

	//���� ������ Init
	{
		//�÷��ι���
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
				CreateFoodData(_Type, _Ingredient, _Cookery)));
		}

		//ġ�����
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
				CreateFoodData(_Type, _Ingredient, _Cookery)));
		}

		//ġ����ž�����丶��
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
				CreateFoodData(_Type, _Ingredient, _Cookery)));
		}

		//������ù�
		{
			FoodType _Type;
			std::vector<IngredientType> _Ingredient;
			std::vector<ToolInfo> _Cookery;

			_Type = FoodType::FishSushimi;
			_Ingredient.push_back(IngredientType::Fish);

			_Cookery.push_back(ToolInfo::None);

			GlobalGameData::AllFoodData_.insert(std::make_pair(_Type,
				CreateFoodData(_Type, _Ingredient, _Cookery)));
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

FoodData InitGlobalGameData::CreateFoodData(FoodType _Type, std::vector<IngredientType>& _Ingredient, std::vector<ToolInfo>& _Cookery)
{
	FoodData NewFoodData;
	NewFoodData.Type = _Type;
	NewFoodData.Ingredient = _Ingredient;
	NewFoodData.Cookery = _Cookery;
	if (_Ingredient.size() != _Cookery.size())
	{
		MsgBoxAssert("Ingredient�� Size�� Cookery�� Size�� �ٸ��ϴ�.");
	}
	return NewFoodData;
}

InitGlobalGameData CreatGlobalGameDataInst = InitGlobalGameData();