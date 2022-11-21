#include "PreCompile.h"
#include "Food_Ingredients_Prawn.h"

GameEngineFBXMesh* Food_Ingredients_Prawn::Mesh_Prawn = nullptr;

Food_Ingredients_Prawn::Food_Ingredients_Prawn()
{
}

Food_Ingredients_Prawn::~Food_Ingredients_Prawn()
{
}

void Food_Ingredients_Prawn::Start()
{
	GamePlayFood::Start();
	GamePlayFood::SetObjectFoodClass(ObjectFoodClass::Prawn);

	//if (Mesh_Prawn == nullptr)
	//{
	//	{
	//		GameEngineDirectory Dir;
	//		Dir.MoveParentToExitsChildDirectory("ContentsResources");
	//		Dir.Move("ContentsResources");
	//		Dir.Move("Mesh");
	//		Dir.Move("Object");
	//		Dir.Move("Stuff");
	//		Dir.Move("Food");
	//		Dir.Move("Ingredient");
	//		Dir.Move("Prawn");

	//		Mesh_Prawn = GameEngineFBXMesh::Load(Dir.PlusFilePath("m_ingredients_prawn_01.FBX"));
	//		std::vector<FBXNodeInfo> Nodes = Mesh_Prawn->CheckAllNode();
	//	}
	//}
	GetFBXMesh()->SetFBXMesh("m_ingredients_prawn_01.FBX", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });


}
//
//CookedStat Food_Ingredients_Prawn::Cook_Start_Child()
//{
//	return CookedStat::Nomal;
//}


//void Food_Ingredients_Prawn::Cook_Update_Child(float _Delta)
//{
//
//}

//GamePlayMoveable* Food_Ingredients_Prawn::Cook_End_Child()
//{
//	GamePlayFood::SetObjectFoodClass(ObjectFoodClass::Prawn_Cutting);
//	// 매시 변경
//	return this;
//}