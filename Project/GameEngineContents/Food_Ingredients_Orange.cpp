#include "PreCompile.h"
#include "Food_Ingredients_Orange.h"

Food_Ingredients_Orange::Food_Ingredients_Orange() 
{
}

Food_Ingredients_Orange::~Food_Ingredients_Orange() 
{
}

void Food_Ingredients_Orange::Start()
{
	GamePlayFood::Start();
	GamePlayFood::SetObjectFoodClass(IngredientType::Orange);

	MeshName_ = "m_ingredients_orange_whole_01.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	//GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });


}

void Food_Ingredients_Orange::TrimmingMixer()
{
	SetTrim();

	ChangeFBXMesh();
	MeshName_ = "m_slice_orange_01.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
}