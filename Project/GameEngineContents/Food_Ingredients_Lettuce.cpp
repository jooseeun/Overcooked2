#include "PreCompile.h"
#include "Food_Ingredients_Lettuce.h"

Food_Ingredients_Lettuce::Food_Ingredients_Lettuce() 
{
}

Food_Ingredients_Lettuce::~Food_Ingredients_Lettuce() 
{
}

void Food_Ingredients_Lettuce::Start()
{
	GamePlayFood::Start();
	GamePlayFood::SetObjectFoodClass(IngredientType::Lettuce);

	MeshName_ = "t_ingredients_lettuce_01_d.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	//GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

void Food_Ingredients_Lettuce::FinishTrimmingFirst()
{
	SetTrim();

	ChangeFBXMesh();
	MeshName_ = "m_ingredients_lettuce_sliced_01.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	GetFBXMesh()->GetTransform().SetLocalRotation({ 0,-90,0 });
}

