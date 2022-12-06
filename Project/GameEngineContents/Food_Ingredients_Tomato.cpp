#include "PreCompile.h"
#include "Food_Ingredients_Tomato.h"

Food_Ingredients_Tomato::Food_Ingredients_Tomato() 
{
}

Food_Ingredients_Tomato::~Food_Ingredients_Tomato() 
{
}

void Food_Ingredients_Tomato::Start()
{
	GamePlayFood::Start();
	GamePlayFood::SetObjectFoodClass(IngredientType::Tomato);

	MeshName_ = "Tomato.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

void Food_Ingredients_Tomato::FinishTrimmingFirst()
{
	SetTrim();

	ChangeFBXMesh();
	MeshName_ = "m_ingredients_tomato_sliced_01.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	GetFBXMesh()->GetTransform().SetLocalRotation({ 0,-90,0 });
}

