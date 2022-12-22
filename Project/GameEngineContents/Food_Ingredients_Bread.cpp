#include "PreCompile.h"
#include "Food_Ingredients_Bread.h"
#include "GamePlayBowl.h"


Food_Ingredients_Bread::Food_Ingredients_Bread() 
{
}

Food_Ingredients_Bread::~Food_Ingredients_Bread() 
{
}

void Food_Ingredients_Bread::Start()
{
	GamePlayFood::Start();
	GamePlayFood::SetObjectFoodClass(IngredientType::Bread);

	MeshName_ = "t_ingredients_bun_01_d.FBX";
	GetFBXMesh()->SetFBXMesh(MeshName_, "Texture");
	//GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });

	SetTrim();
	SetPlatting();

	CombinFood_ = std::make_shared<CombinFood>();
	CombinFood_->Start(0, shared_from_this());
	CombinFood_->PushFood(IngredientType::Bread);
	FoodThumbnail_->Death();
	FoodThumbnail_->Off();
}