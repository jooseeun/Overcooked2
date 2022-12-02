#pragma once
#include "GamePlayBowl.h"

enum class SteamerState
{
	Idle, 
	CookStart,
	Cooking,
	CookDone,
	Max,
};

// Ό³Έν :
class Equipment_Steamer : public GamePlayBowl
{
public:
	// constrcuter destructer
	Equipment_Steamer();
	~Equipment_Steamer();

	// delete Function
	Equipment_Steamer(const Equipment_Steamer& _Other) = delete;
	Equipment_Steamer(Equipment_Steamer&& _Other) noexcept = delete;
	Equipment_Steamer& operator=(const Equipment_Steamer& _Other) = delete;
	Equipment_Steamer& operator=(Equipment_Steamer&& _Other) noexcept = delete;

public:
	inline SteamerState GetSteamerState()
	{
		return SteamerState_;
	}

	inline void SetSteamerState(SteamerState _SteamerState)
	{
		SteamerState_ = _SteamerState;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void CookStartStart(const StateInfo& _Info);
	void CookStartUpdate(float _DeltaTime, const StateInfo& _Info);

	void CookingStart(const StateInfo& _Info);
	void CookingUpdate(float _DeltaTime, const StateInfo& _Info);

	void CookDoneStart(const StateInfo& _Info);
	void CookDoneUpdate(float _DeltaTime, const StateInfo& _Info);

private:
	SteamerState SteamerState_;
	GameEngineStateManager StateManager;

	bool IsInteraction_;
	bool IsOpen_;
	float Angle_;

	std::shared_ptr<GameEngineActor> Lid_;

	// 

	CombineType CombineThis(std::shared_ptr<GamePlayFood> _Food) override;
};

