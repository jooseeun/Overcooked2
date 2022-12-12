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