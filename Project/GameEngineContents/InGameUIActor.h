#pragma once
#include "UIActor.h"
#include "OverCookedUIRenderer.h"
struct FoodData
{
	FoodType Type = FoodType::None;
	std::vector<IngredientType> Ingredient;
	std::vector<ToolInfo> Cookery;
	std::vector<ToolInfo> CommonCookery;
	float WaitingTime = 0.f;
};

struct RecipeSetData
{
	std::string TopBackgroundString = "0";
	float4 BarParentPosNScale = {};// x,y,z : pos w: Scale
	std::vector<float4> IngredientPos;
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
		return ParentRenderer_.lock()->GetTransform();
	}

	float4 GetPos();

	float4 GetScale();

	float4 GetTargetPos()
	{
		return LeftTargetPos_;
	}

	void SetTargetPos(const float4& _Pos) //world
	{
		LeftTargetPos_ = _Pos;
	}

	void SetWorldPosition(const float4& _WorldPos);

	void OpenRecipe();

	float GetLeftTime();
private:
	void Update(float _DeltaTime);

private:
	//주기관련
	bool IsDead_ = false;
	//색깔관련
	float Timeout_IterTime_ = 0.f;
	bool IsTimeOut_;

	bool IsHandOver_ = false;
	float HandOver_IterTime_ = 0.f;
	//pump 관련
	bool IsPumpHori_ = false;
	bool IsPumpVerti_ = false;

	float AccTime_ = 0.f;
	float4 LeftTargetPos_ = {};
	FoodData Data_;

	bool IsRecipeOn_ = false;
	float RecipeOnTime_ = 0.f;

	std::weak_ptr<OverCookedUIRenderer> ParentRenderer_;

	std::weak_ptr<OverCookedUIRenderer> FoodRenderer_;
	std::weak_ptr<OverCookedUIRenderer> TopBackgroundRenderer_;

	//Bar관련
	std::weak_ptr<OverCookedUIRenderer> BarParentRenderer_;
	std::vector< std::weak_ptr<OverCookedUIRenderer>> BarBackgroundRenderer_;
	std::vector< std::weak_ptr<OverCookedUIRenderer>> BarRenderer_;
	std::vector<Timer> BarTimer_;
	Timer GlobalTimer_;

	std::weak_ptr<OverCookedUIRenderer> BottomParentRenderer_;
	std::vector< std::weak_ptr<OverCookedUIRenderer>> BottomBackgroundRenderer_;
	std::vector< std::weak_ptr<OverCookedUIRenderer>> IngredientRenderer_;
	std::vector< std::weak_ptr<OverCookedUIRenderer>> CookeryRenderer_;
};

class InGameUIActor;
class RecipeManager
{
public:
	RecipeManager();
	~RecipeManager();

	inline int GetRecipeCount()
	{
		return static_cast<int>(Recipes_.size());
	}
	void Init(std::weak_ptr<InGameUIActor> _ParentActor_);
	void CreateRecipe(FoodType _Type);
	bool HandOver(FoodType _Type);
	//void DeleteRecipe(std::list<Recipe>::iterator _Iter);
	void Update(float _DeltaTime);

	void DebugFunction();

private:
	void DeleteRecipe(int _Count);

	std::list<Recipe> Recipes_;
	std::weak_ptr<InGameUIActor> ParentActor_;
};

class InGameUIActor : public UIActor
{
	friend GamePlayLevel;
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

	void LevelStartEvent() override;

	void CreateRandomRecipe();

	bool HandOverFood(FoodType _Type);

	RecipeManager RecipeManager_;
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

	Timer NotDeleteRecipe_Timer_; // 10초동안 레시피가 사라지지 않는거 확인하는 타이머
};