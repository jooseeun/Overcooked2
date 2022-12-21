#include "PreCompile.h"
#include "Food_Ingredients_Egg.h"

Food_Ingredients_Egg::Food_Ingredients_Egg() 
{
}

Food_Ingredients_Egg::~Food_Ingredients_Egg() 
{
}

void Food_Ingredients_Egg::Start()
{
	GamePlayFood::Start();
	GamePlayFood::SetObjectFoodClass(IngredientType::Egg);

	MeshName_ = "m_ingredients_egg_01.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	//GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	SetTrim();

}

void Food_Ingredients_Egg::TrimmingPlatting()
{
	//SetTrim();
	//SetPlatting();

	//ChangeFBXMesh();
	//MeshName_ = "Sushi_Roll_Salmon.FBX";
	//GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	//GetFBXMesh()->GetTransform().SetLocalRotation({ 0,-90,0 });
}

void Food_Ingredients_Egg::TrimmingSteam()
{


}