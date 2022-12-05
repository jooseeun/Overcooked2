#include "PreCompile.h"
#include "Food_Ingredients_Prawn.h"

Food_Ingredients_Prawn::Food_Ingredients_Prawn()
{
}

Food_Ingredients_Prawn::~Food_Ingredients_Prawn()
{
}

void Food_Ingredients_Prawn::Start()
{
	GamePlayFood::Start();
	GamePlayFood::SetObjectFoodClass(IngredientType::Prawn);


	MeshName_ = "m_ingredients_prawn_01.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

void Food_Ingredients_Prawn::FinishTrimmingFirst()
{
	SetTrim();

	ChangeFBXMesh();
	MeshName_ = "Prawn_Sushimi.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	GetFBXMesh()->GetTransform().SetLocalRotation({ 0,-90,0 });
}

