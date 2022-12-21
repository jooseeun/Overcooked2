#include "PreCompile.h"
#include "Food_Ingredients_DriedFruit.h"

Food_Ingredients_DriedFruit::Food_Ingredients_DriedFruit() 
{
}

Food_Ingredients_DriedFruit::~Food_Ingredients_DriedFruit() 
{
}

void Food_Ingredients_DriedFruit::Start()
{
	GamePlayFood::Start();
	GamePlayFood::SetObjectFoodClass(IngredientType::DriedFruit);

	MeshName_ = "m_ingredients_driedfruit_01.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	//GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });


}

void Food_Ingredients_DriedFruit::TrimmingMixer()
{
	SetTrim();

	ChangeFBXMesh();
	MeshName_ = "m_prep_driedfruit_01.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
}