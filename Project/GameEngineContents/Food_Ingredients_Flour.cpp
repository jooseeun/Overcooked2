#include "PreCompile.h"
#include "Food_Ingredients_Flour.h"

Food_Ingredients_Flour::Food_Ingredients_Flour() 
{
}

Food_Ingredients_Flour::~Food_Ingredients_Flour() 
{
}

void Food_Ingredients_Flour::Start()
{
	GamePlayFood::Start();
	GamePlayFood::SetObjectFoodClass(IngredientType::Flour);

	MeshName_ = "m_ingredients_flour_01.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	//GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });

	SetTrim();
}

                                                                                                                                                                                    