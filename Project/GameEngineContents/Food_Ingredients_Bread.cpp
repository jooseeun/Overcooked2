#include "PreCompile.h"
#include "Food_Ingredients_Bread.h"

Food_Ingredients_Bread::Food_Ingredients_Bread() 
{
}

Food_Ingredients_Bread::~Food_Ingredients_Bread() 
{
}

void Food_Ingredients_Bread::Start()
{
	GamePlayFood::Start();
	GamePlayFood::SetObjectFoodClass(IngredientType::Bread);

	GetFBXMesh()->SetFBXMesh("t_ingredients_bun_01_d.FBX", "Texture");
	//GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });

	SetTrim();
}