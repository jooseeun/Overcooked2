#include "PreCompile.h"
#include "Food_Ingredients_Cheese.h"

Food_Ingredients_Cheese::Food_Ingredients_Cheese() 
{
}

Food_Ingredients_Cheese::~Food_Ingredients_Cheese() 
{
}

void Food_Ingredients_Cheese::Start()
{
	GamePlayFood::Start();
	GamePlayFood::SetObjectFoodClass(IngredientType::Cheese);

	MeshName_ = "t_ingredients_cheese_01_d.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	//GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

void Food_Ingredients_Cheese::FinishTrimmingFirst()
{
	SetTrim();

	ChangeFBXMesh();
	MeshName_ = "m_ingredients_cheese_sliced_01.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	GetFBXMesh()->GetTransform().SetLocalRotation({ 0,-90,0 });
}

