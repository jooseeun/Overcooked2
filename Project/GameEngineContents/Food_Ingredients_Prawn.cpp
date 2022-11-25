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

	GetFBXMesh()->SetFBXMesh("m_ingredients_prawn_01.FBX", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });


}
