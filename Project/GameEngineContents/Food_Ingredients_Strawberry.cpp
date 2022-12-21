#include "PreCompile.h"
#include "Food_Ingredients_Strawberry.h"

Food_Ingredients_Strawberry::Food_Ingredients_Strawberry() 
{
}

Food_Ingredients_Strawberry::~Food_Ingredients_Strawberry() 
{
}

void Food_Ingredients_Strawberry::Start()
{
	GamePlayFood::Start();
	GamePlayFood::SetObjectFoodClass(IngredientType::Strawberry);

	MeshName_ = "m_ingredients_strawberry_whole_01.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	//GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });


}

void Food_Ingredients_Strawberry::TrimmingMixer()
{
	SetTrim();

	ChangeFBXMesh();
	MeshName_ = "m_slice_strawberry_01.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
}