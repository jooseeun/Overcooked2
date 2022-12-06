#include "PreCompile.h"
#include "Food_Ingredients_Meat.h"

Food_Ingredients_Meat::Food_Ingredients_Meat() 
{
}

Food_Ingredients_Meat::~Food_Ingredients_Meat() 
{
}

void Food_Ingredients_Meat::Start()
{
	GamePlayFood::Start();
	GamePlayFood::SetObjectFoodClass(IngredientType::Meat);

	MeshName_ = "t_ingredients_meat_01_d.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	//GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

void Food_Ingredients_Meat::FinishTrimmingFirst()
{
	SetTrim();

	ChangeFBXMesh();
	MeshName_ = "m_prep_meat_burger_01.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	GetFBXMesh()->GetTransform().SetLocalRotation({ 0,-90,0 });
}

