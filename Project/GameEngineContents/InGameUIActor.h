#pragma once
#include "UIActor.h"
#include "OverCookedUIRenderer.h"
struct FoodData
{
	FoodType Type = FoodType::None;
	std::vector<IngredientType> Ingredient;
	std::vector<ToolInfo> Cookery;
};

struct RecipeSetData
{
	std::string TopBackgroundString = "0";
	float4 BarParentPosNScale = {};// x,y,z : pos w: Scale
};

class RecipeManager;
class Recipe
{
	friend RecipeManager;
public:
	Recipe(FoodType _Type);
	~Recipe();

	RecipeSetData GetRecipeSetData();

	GameEngineTransform& GetParentRenderer_Transform()
	{
		return ParentRenderer_->GetTransform();
	}

private:
	FoodData Data_;
	std::shared_ptr<OverCookedUIRenderer> ParentRenderer_;

	std::shared_ptr<OverCookedUIRenderer> FoodRenderer_;
	std::shared_ptr<OverCookedUIRenderer> TopBackgroundRenderer_;

	std::shared_ptr<OverCookedUIRenderer> BarParentRenderer_;
	std::vector< std::shared_ptr<OverCookedUIRenderer>> BarRenderer_;

	std::shared_ptr<OverCookedUIRenderer> BottomParentRenderer_;
	std::vector< std::shared_ptr<OverCookedUIRenderer>> BottomBackgroundRenderer_;
	std::vector< std::shared_ptr<OverCookedUIRenderer>> IngredientRenderer_;
};

class InGameUIActor;
class RecipeManager
{
public:
	RecipeManager();
	~RecipeManager();

	void Init(std::shared_ptr<InGameUIActor> _ParentActor_);
	void CreateRecipe(FoodType _Type);

private:

	std::vector<Recipe> Recipes_;
	std::shared_ptr<InGameUIActor> ParentActor_;
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