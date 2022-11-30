#include "PreCompile.h"
#include "InGameUIActor.h"
#include "GlobalGameData.h"

#include "OverCookedUIRenderer.h"
#include "ContentsUtility.h"

using namespace ContentsUtility;
using namespace UI_Utility;
RecipeManager::RecipeManager()
{
	//
}

RecipeManager::~RecipeManager()
{
	Recipes_.clear();
}

void RecipeManager::Init(std::weak_ptr<InGameUIActor> _ParentActor_)
{
	ParentActor_ = _ParentActor_;
}

void RecipeManager::CreateRecipe(FoodType _Type)
{
	Recipe NewRecipe(_Type);

	NewRecipe.ParentRenderer_ = ParentActor_.lock()->CreateUIRenderer("Top_Recipe_Background.png");
	NewRecipe.ParentRenderer_.lock()->GetTransform().SetLocalScale({ 1.f,1.f,1.f });
	NewRecipe.ParentRenderer_.lock()->Off();
	NewRecipe.ParentRenderer_.lock()->ResistDebug();

	NewRecipe.BottomParentRenderer_ = ParentActor_.lock()->CreateUIRenderer("Top_Recipe_Background.png", "BottomParent");
	NewRecipe.BottomParentRenderer_.lock()->GetTransform().SetLocalScale({ 1.f,1.f,1.f });
	NewRecipe.BottomParentRenderer_.lock()->Off();
	NewRecipe.BottomParentRenderer_.lock()->ResistDebug();
	NewRecipe.BottomParentRenderer_.lock()->GetTransform().SetParentTransform(NewRecipe.ParentRenderer_.lock()->GetTransform());

	RecipeSetData Data = NewRecipe.GetRecipeSetData();

	//Top Background
	NewRecipe.TopBackgroundRenderer_ = ParentActor_.lock()->CreateUIRenderer("Top_Recipe_Background" + Data.TopBackgroundString + ".png");
	NewRecipe.TopBackgroundRenderer_.lock()->GetTransform().SetParentTransform(NewRecipe.ParentRenderer_.lock()->GetTransform());

	//Bar Parent
	NewRecipe.BarParentRenderer_ = ParentActor_.lock()->CreateUIRenderer("Top_Recipe_Background.png", "BarParent");
	NewRecipe.BarParentRenderer_.lock()->GetTransform().SetLocalScale({ 1.f,1.f,1.f });
	NewRecipe.BarParentRenderer_.lock()->GetTransform().SetLocalPosition({ Data.BarParentPosNScale.x,Data.BarParentPosNScale.y });
	NewRecipe.BarParentRenderer_.lock()->Off();
	NewRecipe.BarParentRenderer_.lock()->ResistDebug();
	NewRecipe.BarParentRenderer_.lock()->GetTransform().SetParentTransform(NewRecipe.ParentRenderer_.lock()->GetTransform());

	//BarBackground
	{
		float Inter = 2.f;
		for (int i = 0; i < 3; i++)
		{
			std::weak_ptr<OverCookedUIRenderer> NewRenderer = ParentActor_.lock()->CreateUIRenderer("RecipeBar.png", "Bar");
			NewRenderer.lock()->GetTransform().SetParentTransform(NewRecipe.BarParentRenderer_.lock()->GetTransform());
			float ScaleX = NewRenderer.lock()->GetTransform().GetWorldScale().x;
			float4 Pos = { (ScaleX + Inter) * (i - 1),0,0 };
			NewRenderer.lock()->GetTransform().SetLocalPosition(Pos);
			NewRecipe.BarBackgroundRenderer_.push_back(NewRenderer);
			//NewRenderer->GetTransform().SetLocalPosition()
		}
	}
	//Bar
	{
		float Inter = 2.f;
		for (int i = 0; i < 3; i++)
		{
			std::weak_ptr<OverCookedUIRenderer> NewRenderer = ParentActor_.lock()->CreateUIRenderer("RecipeBar.png", "Bar");
			NewRenderer.lock()->GetTransform().SetParentTransform(NewRecipe.BarParentRenderer_.lock()->GetTransform());
			float ScaleX = NewRenderer.lock()->GetTransform().GetWorldScale().x;
			float4 Pos = { (ScaleX + Inter) * (i - 1),0,0 };
			NewRenderer.lock()->GetTransform().SetLocalPosition(Pos);
			NewRecipe.BarRenderer_.push_back(NewRenderer);
			//NewRenderer->GetTransform().SetLocalPosition()
		}
	}

	//FoodIcon
	NewRecipe.FoodRenderer_ = ParentActor_.lock()->CreateUIRenderer(EnumToString(NewRecipe.Data_.Type), 0.50f);
	NewRecipe.FoodRenderer_.lock()->ResistDebug();
	NewRecipe.FoodRenderer_.lock()->GetTransform().SetParentTransform(NewRecipe.ParentRenderer_.lock()->GetTransform());

	//BottomBackground && Cookery
	{
		//Tool 파악
		if (NewRecipe.Data_.CommonCookery.empty() == true)
		{
			//BottomBackground
			for (int i = 0; i < NewRecipe.Data_.Ingredient.size(); i++)
			{
				std::weak_ptr<OverCookedUIRenderer> NewRenderer;
				if (NewRecipe.Data_.Cookery[i] == ToolInfo::None)
				{
					NewRenderer = ParentActor_.lock()->CreateUIRenderer("Recipe_Background0.png");
				}
				else
				{
					NewRenderer = ParentActor_.lock()->CreateUIRenderer("Recipe_Background1.png");
				}
				NewRenderer.lock()->GetTransform().SetParentTransform(NewRecipe.BottomParentRenderer_.lock()->GetTransform());
				float ScaleX = NewRenderer.lock()->GetTransform().GetWorldScale().x;
				float4 Pos = Data.IngredientPos[i];
				if (NewRecipe.Data_.Cookery[i] != ToolInfo::None)
				{
					Pos.y -= 22.5f;
				}
				NewRenderer.lock()->GetTransform().SetLocalPosition(Pos);
				NewRecipe.BottomBackgroundRenderer_.push_back(NewRenderer);
			}

			//Cookery
			for (int i = 0; i < NewRecipe.Data_.Ingredient.size(); i++)
			{
				if (NewRecipe.Data_.Cookery[i] == ToolInfo::None)
				{
					continue;
				}
				std::weak_ptr<OverCookedUIRenderer> NewRenderer = ParentActor_.lock()->CreateUIRenderer(EnumToString(NewRecipe.Data_.Cookery[i]), 0.38f);
				NewRenderer.lock()->GetTransform().SetParentTransform(NewRecipe.BottomParentRenderer_.lock()->GetTransform());
				float ScaleX = NewRenderer.lock()->GetTransform().GetWorldScale().x;
				float4 Pos = Data.IngredientPos[i];
				Pos.y -= 42.f;
				NewRenderer.lock()->GetTransform().SetLocalPosition(Pos);
				NewRecipe.CookeryRenderer_.push_back(NewRenderer);
			}
		}
		else //commonCookery
		{
			//BottomBackground
			for (int i = 0; i < NewRecipe.Data_.Ingredient.size(); i++)
			{
				std::weak_ptr<OverCookedUIRenderer> NewRenderer;
				NewRenderer = ParentActor_.lock()->CreateUIRenderer("Recipe_Background2.png");
				NewRenderer.lock()->GetTransform().SetParentTransform(NewRecipe.BottomParentRenderer_.lock()->GetTransform());
				float4 Pos = { 0,-22.5f,0 };
				NewRenderer.lock()->GetTransform().SetLocalPosition(Pos);
				NewRecipe.BottomBackgroundRenderer_.push_back(NewRenderer);
			}

			//Cookery
			for (int i = 0; i < NewRecipe.Data_.CommonCookery.size(); i++)
			{
				std::weak_ptr<OverCookedUIRenderer> NewRenderer = ParentActor_.lock()->CreateUIRenderer(EnumToString(NewRecipe.Data_.CommonCookery[i]), 0.38f);
				NewRenderer.lock()->GetTransform().SetParentTransform(NewRecipe.BottomParentRenderer_.lock()->GetTransform());
				float ScaleX = NewRenderer.lock()->GetTransform().GetWorldScale().x;
				float4 Pos = Data.IngredientPos[i];
				Pos.y -= 42.f;
				NewRenderer.lock()->GetTransform().SetLocalPosition(Pos);
				NewRecipe.CookeryRenderer_.push_back(NewRenderer);
			}
		}
	}

	//IngredientIcon
	{
		for (int i = 0; i < NewRecipe.Data_.Ingredient.size(); i++)
		{
			std::weak_ptr<OverCookedUIRenderer> NewRenderer = ParentActor_.lock()->CreateUIRenderer(EnumToString(NewRecipe.Data_.Ingredient[i]), 0.265f);
			NewRenderer.lock()->GetTransform().SetParentTransform(NewRecipe.BottomParentRenderer_.lock()->GetTransform());
			float ScaleX = NewRenderer.lock()->GetTransform().GetWorldScale().x;
			float4 Pos = Data.IngredientPos[i];
			NewRenderer.lock()->GetTransform().SetLocalPosition(Pos);
			NewRecipe.IngredientRenderer_.push_back(NewRenderer);
		}
	}

	//Parent위치이동
	//이걸 왜 여기서 다시하냐고? > 처음에 BarParent의 Sclae을 1.f로 하고 나서 Bar을 변환하지 않으면 Bar의 Transform이 무너져
	NewRecipe.BarParentRenderer_.lock()->GetTransform().SetLocalScale({ Data.BarParentPosNScale.w,1.f,1.f });
	NewRecipe.ParentRenderer_.lock()->GetTransform().SetLocalPosition({ 230.f * (Recipes_.size()),327,0 });
	NewRecipe.BottomParentRenderer_.lock()->GetTransform().SetLocalPosition({ 0,-52.f,1 });

	Recipes_.push_back(NewRecipe);
}

void RecipeManager::Update(float _DeltaTime)
{
	for (int i = 0; i < Recipes_.size(); i++)
	{
		Recipes_[i].Update(_DeltaTime);
	}
}

Recipe::Recipe(FoodType _Type)
{
	Data_ = GlobalGameData::GetFoodData(_Type); //복사가 일어남

	float LeftTime = Data_.WaitingTime / 3.f;
	GlobalTimer_.StartTimer(Data_.WaitingTime);
	for (int i = 0; i < 3; i++)
	{
		Timer NewTimer;
		NewTimer.StartTimer(LeftTime);
		BarTimer_.push_back(NewTimer);
	}
}

Recipe::~Recipe()
{
	BarBackgroundRenderer_.clear();
	BarRenderer_.clear();
	BottomBackgroundRenderer_.clear();
	IngredientRenderer_.clear();
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

		std::vector<float4> Arr;
		Arr.push_back({ -22.5,0,0 });
		NewData.IngredientPos = Arr;
		break;
	}
	case 2:
	{
		NewData.TopBackgroundString = "0";
		NewData.BarParentPosNScale = { 0.f,23.f,0,1.02f };
		std::vector<float4> Arr;
		Arr.push_back({ -22.5,0,0 });
		Arr.push_back({ 22.5,0,0 });
		NewData.IngredientPos = Arr;
		break;
	}
	case 3:
	{
		NewData.TopBackgroundString = "1";
		NewData.BarParentPosNScale = { 0.f,23.f,0,1.62f };
		std::vector<float4> Arr;
		Arr.push_back({ -45,0,0 });
		Arr.push_back({ 0,0,0 });
		Arr.push_back({ 45,0,0 });
		NewData.IngredientPos = Arr;
		break;
	}
	case 4:
	{
		NewData.TopBackgroundString = "2";
		NewData.BarParentPosNScale = { 0.f,23.f,0,2.12f };
		std::vector<float4> Arr;
		Arr.push_back({ -67.5,0,0 });
		Arr.push_back({ -22.5,0,0 });
		Arr.push_back({ 22.5,0,0 });
		Arr.push_back({ 67.5,0,0 });
		NewData.IngredientPos = Arr;
		break;
	}
	default:
		break;
	}
	return NewData;
}

void Recipe::Update(float _DeltaTime)
{
	if (GlobalTimer_.IsTimeOver() == false)
	{
		GlobalTimer_.Update(_DeltaTime);
	}
	if (BarTimer_[2].IsTimeOver() == false)
	{
		BarTimer_[2].Update(_DeltaTime);
	}
	else
	{
		if (BarTimer_[1].IsTimeOver() == false)
		{
			BarTimer_[1].Update(_DeltaTime);
		}
		else
		{
			if (BarTimer_[0].IsTimeOver() == false)
			{
				BarTimer_[0].Update(_DeltaTime);
			}
		}
	}

	for (int i = 2; i >= 0; i--)
	{
		float Percentage = BarTimer_[i].GetCurTime() / BarTimer_[i].Default_Time_;
		BarRenderer_[i].lock()->UpdateLeftToRight(Percentage);

		float GlobalPercentage = GlobalTimer_.GetCurTime() / GlobalTimer_.Default_Time_;
		BarRenderer_[i].lock()->UpdateLeftTime(GlobalPercentage);
	}
	//TimeGauge
	//float Percentage = LeftTimer.GetCurTime() / GlobalGameData::GetMaxTime();
	//TimerUIInst_.Bar->UpdateLeftToRight(Percentage);
	//TimerUIInst_.Bar->UpdateLeftTime(Percentage);
}