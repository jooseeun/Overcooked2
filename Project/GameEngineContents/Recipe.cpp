#include "PreCompile.h"
#include "InGameUIActor.h"
#include "GlobalGameData.h"

#include "OverCookedUIRenderer.h"

RecipeManager::RecipeManager()
{
	//
}

RecipeManager::~RecipeManager()
{
}

void RecipeManager::Init(std::shared_ptr<InGameUIActor> _ParentActor_)
{
	ParentActor_ = _ParentActor_;
}

void RecipeManager::CreateRecipe(FoodType _Type)
{
	Recipe NewRecipe(_Type);

	NewRecipe.ParentRenderer_ = ParentActor_->CreateUIRenderer("Top_Recipe_Background.png");
	NewRecipe.ParentRenderer_->GetTransform().SetLocalScale({ 1.f,1.f,1.f });
	//NewRecipe.ParentRenderer_->GetTransform().SetLocalPosition({ 0,327,0 });

	NewRecipe.ParentRenderer_->Off();
	NewRecipe.ParentRenderer_->ResistDebug();

	RecipeSetData Data = NewRecipe.GetRecipeSetData();

	//Top Background
	NewRecipe.TopBackgroundRenderer_ = ParentActor_->CreateUIRenderer("Top_Recipe_Background" + Data.TopBackgroundString + ".png");
	NewRecipe.TopBackgroundRenderer_->GetTransform().SetParentTransform(NewRecipe.ParentRenderer_->GetTransform());

	//Bar Parent
	NewRecipe.BarParentRenderer_ = ParentActor_->CreateUIRenderer("Top_Recipe_Background.png", "BarParent");
	NewRecipe.BarParentRenderer_->GetTransform().SetLocalScale({ 1.f,1.f,1.f });
	NewRecipe.BarParentRenderer_->GetTransform().SetLocalPosition({ Data.BarParentPosNScale.x,Data.BarParentPosNScale.y });
	NewRecipe.BarParentRenderer_->Off();
	NewRecipe.BarParentRenderer_->ResistDebug();
	NewRecipe.BarParentRenderer_->GetTransform().SetParentTransform(NewRecipe.ParentRenderer_->GetTransform());

	//Bar
	{
		float Inter = 2.f;
		for (int i = 0; i < 3; i++)
		{
			std::shared_ptr<OverCookedUIRenderer> NewRenderer = ParentActor_->CreateUIRenderer("RecipeBar.png", "Bar");
			NewRenderer->GetTransform().SetParentTransform(NewRecipe.BarParentRenderer_->GetTransform());
			float ScaleX = NewRenderer->GetTransform().GetWorldScale().x;
			float4 Pos = { (ScaleX + Inter) * (i - 1),0,0 };
			NewRenderer->GetTransform().SetLocalPosition(Pos);
			NewRecipe.BarRenderer_.push_back(NewRenderer);
			//NewRenderer->GetTransform().SetLocalPosition()
		}
	}

	//이걸 왜 여기서 다시하냐고? > 처음에 BarParent의 Sclae을 1.f로 하고 나서 Bar을 변환하지 않으면 Bar의 Transform이 무너져
	NewRecipe.BarParentRenderer_->GetTransform().SetLocalScale({ Data.BarParentPosNScale.w,1.f,1.f });

	NewRecipe.ParentRenderer_->GetTransform().SetLocalPosition({ 230.f * (Recipes_.size()),327,0 });

	Recipes_.push_back(NewRecipe);
}

Recipe::Recipe(FoodType _Type)
{
	//Type_ = _Type;
	Data_ = GlobalGameData::GetFoodData(_Type); //복사가 일어남
}

Recipe::~Recipe()
{
}

RecipeSetData Recipe::GetRecipeSetData()
{
	RecipeSetData NewData;

	switch (Data_.Ingredient.size())
	{
	case 1:
	{
		NewData.TopBackgroundString = "0";
		NewData.BarParentPosNScale = { 0.f,23.f,0,1.02f };
		break;
	}
	case 2:
	{
		NewData.TopBackgroundString = "0";
		NewData.BarParentPosNScale = { 0.f,23.f,0,1.02f };

		break;
	}
	case 3:
	{
		NewData.TopBackgroundString = "1";
		NewData.BarParentPosNScale = { 0.f,23.f,0,1.62f };
		break;
	}
	case 4:
	{
		NewData.TopBackgroundString = "2";
		NewData.BarParentPosNScale = { 0.f,23.f,0,2.12f };
		break;
	}
	default:
		break;
	}
	return NewData;
}