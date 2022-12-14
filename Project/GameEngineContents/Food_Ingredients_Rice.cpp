#include "PreCompile.h"
#include "Food_Ingredients_Rice.h"

Food_Ingredients_Rice::Food_Ingredients_Rice() 
{
}

Food_Ingredients_Rice::~Food_Ingredients_Rice() 
{
}


void Food_Ingredients_Rice::Start()
{
	GamePlayFood::Start();
	GamePlayFood::SetObjectFoodClass(IngredientType::Rice);


	MeshName_ = "m_ingredients_rice_01.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	//GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });

	SetTrim();
}

void Food_Ingredients_Rice::FinishTrimmingFirst()
{
	Function_TrimmingType_();
}

void Food_Ingredients_Rice::TrimmingBoil()
{
	MeshName_ = "t_ingredients_rice_trimming.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 0.9f, 0.9f, 0.9f });

	SetPlatting();
}