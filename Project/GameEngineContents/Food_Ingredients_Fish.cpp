#include "PreCompile.h"
#include "Food_Ingredients_Fish.h"
#include "GlobalGameData.h"

Food_Ingredients_Fish::Food_Ingredients_Fish() 
{
}

Food_Ingredients_Fish::~Food_Ingredients_Fish() 
{
}

void Food_Ingredients_Fish::Start()
{
	GamePlayFood::Start();
	GamePlayFood::SetObjectFoodClass(IngredientType::Fish);

	MeshName_ = "m_ingredients_fish_01.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });

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
					if (Data.Cookery[j] == ToolInfo::None)
					{
						SetCookingType(CookingType::Default);
					}
					else
					{
						SetCookingType(CookingType::User0);
					}
				}
				else
				{
					SetCookingType(CookingType::User0);
				}
			}
		}
	}
}

void Food_Ingredients_Fish::FinishTrimmingFirst()
{	
	switch (GetCookingType())
	{
	case CookingType::Default:
		TrimmingSushi();
		break;
	case CookingType::User0:
		TrimmingSteam();
		break;
	case CookingType::User1:
		break;
	default:
		break;
	}
}

void Food_Ingredients_Fish::TrimmingSushi()
{
	SetTrim();
	SetPlatting();

	ChangeFBXMesh();
	MeshName_ = "Sushi_Roll_Salmon.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	GetFBXMesh()->GetTransform().SetLocalRotation({ 0,-90,0 });
}
void Food_Ingredients_Fish::TrimmingSteam()
{

	
}