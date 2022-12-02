#include "PreCompile.h"
#include "Food_Ingredients_Fish.h"

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

	GetFBXMesh()->SetFBXMesh("m_ingredients_fish_01.FBX", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	
}

void Food_Ingredients_Fish::FinishTrimmingFirst()
{
	SetTrim();
	GetFBXMesh()->SetFBXMesh("Sushi_Roll_Salmon.FBX", "Texture");
}