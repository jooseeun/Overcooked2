#include "PreCompile.h"
#include "Food_Ingredients_Blueberry.h"

Food_Ingredients_Blueberry::Food_Ingredients_Blueberry() 
{
}

Food_Ingredients_Blueberry::~Food_Ingredients_Blueberry() 
{
}

void Food_Ingredients_Blueberry::Start()
{
	GamePlayFood::Start();
	GamePlayFood::SetObjectFoodClass(IngredientType::Blueberry);

	MeshName_ = "m_dlc5_ingredients_blueberry_01.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	//GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });


}
void Food_Ingredients_Blueberry::TrimmingMixer()
{
	SetTrim();

	ChangeFBXMesh();
	MeshName_ = "m_dlc5_prep_blueberry_01.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
}