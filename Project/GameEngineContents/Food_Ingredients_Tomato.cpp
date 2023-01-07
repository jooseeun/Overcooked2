#include "PreCompile.h"
#include "Food_Ingredients_Tomato.h"

Food_Ingredients_Tomato::Food_Ingredients_Tomato() 
{
}

Food_Ingredients_Tomato::~Food_Ingredients_Tomato() 
{
}

void Food_Ingredients_Tomato::Start()
{
	GamePlayFood::Start();
	GamePlayFood::SetObjectFoodClass(IngredientType::Tomato);

	MeshName_ = "Tomato.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

//void Food_Ingredients_Tomato::Update(float _DeltaTime)
//{
//	GameEngineDebug::OutPutString(std::to_string(GetTransform().GetWorldScale().x) + " + " + std::to_string(GetTransform().GetWorldScale().y));
//	GameEngineDebug::OutPutString("//////////////////////////////////////////////////////////////////////////////////////////////////");
//}


void Food_Ingredients_Tomato::TrimmingPlatting()
{
	SetTrim();
	SetPlatting();

	ChangeFBXMesh();
	MeshName_ = "m_ingredients_tomato_sliced_01.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 8, 8, 8});
	GetFBXMesh()->GetTransform().SetLocalRotation({ 0,-90,0 });
}

