#include "PreCompile.h"
#include "Food_Ingredients_Carrot.h"

Food_Ingredients_Carrot::Food_Ingredients_Carrot() 
{
}

Food_Ingredients_Carrot::~Food_Ingredients_Carrot() 
{
}

void Food_Ingredients_Carrot::Start()
{
	GamePlayFood::Start();
	GamePlayFood::SetObjectFoodClass(IngredientType::Carrot);

	MeshName_ = "m_ingredients_Carrot_01.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	GetFBXMesh()->GetTransform().SetWorldRotation({ 0, 90, 0});

}

void Food_Ingredients_Carrot::TrimmingMixer()
{
	SetTrim();

	ChangeFBXMesh();
	MeshName_ = "m_ingredients_Carrot_01_Trim.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100 , 100 });
}