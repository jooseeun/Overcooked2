#include "PreCompile.h"
#include "Food_Ingredients_Seaweed.h"

Food_Ingredients_Seaweed::Food_Ingredients_Seaweed() 
{
}

Food_Ingredients_Seaweed::~Food_Ingredients_Seaweed() 
{
}

void Food_Ingredients_Seaweed::Start()
{
	GamePlayFood::Start();
	GamePlayFood::SetObjectFoodClass(IngredientType::Seaweed);

	MeshName_ = "t_ingredients_seaweed_01_d.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	//GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });

	SetTrim();
	SetPlatting();
}