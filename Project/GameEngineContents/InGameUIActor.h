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
	int Score = 10;
};

struct RecipeSetData
{
	std::string TopBackgroundString = "0";
	float4 BarParentPosNScale = {};// x,y,z : pos w: Scale
	std::vector<float4> IngredientPos;
};

class GameScore;
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

	std::vector<int> GetScore();
private:
	void Update(float _DeltaTime);

	void UpdateTime(float _DeltaTime, bool IsHost = true);

private:
	//주기관련
	bool IsDead_ = false;
	//색깔관련
	float Timeout_IterTime_ = 0.f;
	bool IsTimeOut_;
	bool FailFlag_ = false;

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

	//서버 동기화 관련
	Timer FailSyncTimer_;//Fail해서 빨간색되면 약 3초동안 다시 빨간색 되는 것을 방지하는 타이머

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

class GameScore;
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
	void Init(std::weak_ptr<InGameUIActor> _ParentActor_, std::function<void(int, int, bool)> _HandOverFunction, std::function<void(int)> _FailFunction); //앞int : 음식 Score, 뒷 int : 팁 점수
	void CreateRecipe(FoodType _Type);
	bool HandOver(FoodType _Type);
	//void DeleteRecipe(std::list<Recipe>::iterator _Iter);
	void Update(float _DeltaTime);

	void DebugFunction();

	//시간 동기화 관련
	std::vector<float> GetRecipeTime();
	void UpdateFixedTime(std::vector<float> _Vector);

	bool IsHost_ = false;
private:
	std::vector<float> GlobalTimeVector_;

private:
	void DeleteRecipe(int _Count);

	std::list<Recipe> Recipes_;
	std::weak_ptr<InGameUIActor> ParentActor_;

	std::function<void(int, int, bool)> HandOverScore_;
	std::function<void(int)> FailScore_;
};

class InGameUIActor : public UIActor, public  GameServerObject
{
	friend GamePlayLevel;
public:
	InGameUIActor();
	~InGameUIActor();

	InGameUIActor(const InGameUIActor& _Other) = delete;
	InGameUIActor(const InGameUIActor&& _Other) noexcept = delete;
	InGameUIActor& operator=(const InGameUIActor& _Ohter) = delete;
	InGameUIActor& operator=(const InGameUIActor&& _Other) noexcept = delete;

	void ServerInit();
	void ServerRelease();
private:
	bool IsInit_ = false;
protected:
	void UIStart() override;
	void UIUpdate(float _DeltaTime) override;

	void UpdateIsStart(float _DeltaTime);

	void UpdateTime(float _DeltaTime);
	void UpdateScore(float _DeltaTime);

	void LevelStartEvent() override;

	void CreateRandomRecipe();
	bool RequestHandOverFood(FoodType _Type);

	bool HandOverFood(FoodType _Type);

	void HandOverScore(int _FoodScore, int _FoodTips, bool IsLeft);

	void FailScore(int _FoodScore);

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
		std::shared_ptr<OverCookedUIRenderer> Bar;
		std::shared_ptr<GameEngineFontRenderer> TipGaugeFontFrontground;

		std::shared_ptr<OverCookedUIRenderer> BarBackground;
		std::shared_ptr<GameEngineUIRenderer> Coin;
		std::shared_ptr<GameEngineUIRenderer> Fire;

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

	//시작 , 종료 UI 관련
	std::weak_ptr<OverCookedUIRenderer> ReadyRenderer_;
	std::weak_ptr<OverCookedUIRenderer> StartRenderer_;
	std::weak_ptr<OverCookedUIRenderer> TimeUpRenderer_;
	Timer TimeUpDefenseTimer_;

	Timer ReadyTimer_;
	Timer StartTimer_;
	Timer TimeUpTimer_;
	SyncManager ReadySycn_;

	//서버
private:
	void ServerStart();
	void ServerUpdate(float _DeltaTime);

	//public:
	//	static int MaxPlayerCount_;
	//	static int PlayerCount_;
	//	static std::shared_ptr<Player> GetMyPlayer()
	//	{
	//		return MyPlayer;
	//	}
	//
	//	static void SetMyPlayer(std::shared_ptr<Player> _Player)
	//	{
	//		MyPlayer = _Player;
	//	}
};