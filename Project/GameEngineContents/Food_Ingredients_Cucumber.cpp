#include "PreCompile.h"
#include "Food_Ingredients_Cucumber.h"

Food_Ingredients_Cucumber::Food_Ingredients_Cucumber() 
{
}

Food_Ingredients_Cucumber::~Food_Ingredients_Cucumber() 
{
}

void Food_Ingredients_Cucumber::Start()
{
	GamePlayFood::Start();
	GamePlayFood::SetObjectFoodClass(IngredientType::Cucumber);

	MeshName_ = "m_ingredients_cucumber_01.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	//GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });

}

void Food_Ingredients_Cucumber::FinishTrimmingFirst()
{
	Function_TrimmingType_();
}

void Food_Ingredients_Cucumber::TrimmingPlatting()
{
	SetTrim();
	SetPlatting();

	ChangeFBXMesh();
	MeshName_ = "t_ingredients_cucumber_trimming.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	//GetFBXMesh()->GetTransform().SetLocalRotation({ 0,-90,0 });
}
