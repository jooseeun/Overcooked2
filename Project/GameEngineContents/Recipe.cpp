#include "PreCompile.h"
#include "InGameUIActor.h"
#include "GlobalGameData.h"

RecipeManager::RecipeManager()
{
}

RecipeManager::~RecipeManager()
{
}

void RecipeManager::CreateRecipe(FoodType _Type)
{
	Recipe NewRecipe(_Type);
	Recipes_.push_back(NewRecipe);
}

Recipe::Recipe(FoodType _Type)
{
	//Type_ = _Type;
	Data_ = GlobalGameData::GetFoodData(_Type); //복사가 일어남
}

Recipe::~Recipe()
{
}