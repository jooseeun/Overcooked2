#pragma once
#include "UIActor.h"

struct FoodData
{
	FoodType Type = FoodType::None;
	std::vector<IngredientType> Ingredient;
	std::vector<ToolInfo> Cookery;
};

class Recipe
{
public:
	Recipe(FoodType _Type);
	~Recipe();

private:
	FoodData Data_;
	std::shared_ptr<OverCookedUIRenderer> ParentRenderer_;

	std::shared_ptr<OverCookedUIRenderer> TopBackgroundRenderer_;
	std::vector< std::shared_ptr<OverCookedUIRenderer>> BottomBackgroundRenderer_;

	std::vector< std::shared_ptr<OverCookedUIRenderer>> BarRenderer_;

	std::vector< std::shared_ptr<OverCookedUIRenderer>> IngredientRenderer_;
	std::shared_ptr<OverCookedUIRenderer> FoodRenderer_;
};

class RecipeManager
{
public:
	RecipeManager();
	~RecipeManager();

	void CreateRecipe(FoodType _Type);
private:
	std::vector<Recipe> Recipes_;
};

class InGameUIActor : public UIActor
{
public:
	InGameUIActor();
	~InGameUIActor();

	InGameUIActor(const InGameUIActor& _Other) = delete;
	InGameUIActor(const InGameUIActor&& _Other) noexcept = delete;
	InGameUIActor& operator=(const InGameUIActor& _Ohter) = delete;
	InGameUIActor& operator=(const InGameUIActor&& _Other) noexcept = delete;

protected:
	void UIStart() override;
	void UIUpdate(float _DeltaTime) override;

	void UpdateTime(float _DeltaTime);

private:
	struct TimerUI
	{
		std::shared_ptr<OverCookedUIRenderer> Banner;
		std::shared_ptr<OverCookedUIRenderer> Bar;
		std::shared_ptr<OverCookedUIRenderer> BarBackground;
		std::shared_ptr<OverCookedUIRenderer> HourGlass;
		std::shared_ptr<GameEngineFontRenderer> Time;
	};

	struct ScoreUI
	{
		std::shared_ptr<OverCookedUIRenderer> Banner;
		std::shared_ptr<OverCookedUIRenderer> BarBackground;
		std::shared_ptr<GameEngineUIRenderer> Coin;

		std::shared_ptr<GameEngineFontRenderer> Score;
	};

	TimerUI TimerUIInst_;
	ScoreUI ScoreUIInst_;

	//Score
	int CurScore_ = 0;

	float Under30_ = 0.f;

	float GetScoreIter_ = 0.f;
	bool IsGetScore_ = false;

	RecipeManager RecipeManager_;
};