#include "PreCompile.h"
#include "Food_Ingredients_Fish.h"
#include "GlobalGameData.h"

Food_Ingredients_Fish::Food_Ingredients_Fish() 
{
}

Food_Ingredients_Fish::~Food_Ingredients_Fish() 
{
}

void Food_Ingredients_Fish::Start()
{
	GamePlayFood::Start();
	GamePlayFood::SetObjectFoodClass(IngredientType::Fish);

	MeshName_ = "m_ingredients_fish_01.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });


}

void Food_Ingredients_Fish::TrimmingPlatting()
{
	SetTrim();
	SetPlatting();

	ChangeFBXMesh();
	MeshName_ = "Sushi_Roll_Salmon.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	GetFBXMesh()->GetTransform().SetLocalRotation({ 0,-90,0 });
}
void Food_Ingredients_Fish::TrimmingMixer()
{
	SetTrim();
//	SetPlatting();

	ChangeFBXMesh();
	MeshName_ = "m_ingredients_fish_sliced.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	//GetFBXMesh()->GetTransform().SetLocalRotation({ 0,-90,0 });
}

void Food_Ingredients_Fish::TrimmingSteam()
{
	SetTrim();
	//	SetPlatting();

	ChangeFBXMesh();
	MeshName_ = "m_ingredients_fish_sliced.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	//GetFBXMesh()->GetTransform().SetLocalRotation({ 0,-90,0 });
}

