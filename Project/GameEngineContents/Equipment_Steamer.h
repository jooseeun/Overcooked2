#pragma once
#include "GamePlayBowl.h"

enum class SteamerState
{
	Idle, 
	Cooking,
	Open,
	Close,
	Max,
};

// Ό³Έν :
class Equipment_Steamer : public GamePlayBowl
{
	friend class Equipment_Bowl;
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
	inline void SetSteamerState(SteamerState _SteamerState)
	{
		SteamerState_ = _SteamerState;
	}

	inline void SwitchInteraction()
	{
		IsInteraction_ = !IsInteraction_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void OpenStart(const StateInfo& _Info);
	void OpenUpdate(float _DeltaTime, const StateInfo& _Info);

	void CookingStart(const StateInfo& _Info);
	void CookingUpdate(float _DeltaTime, const StateInfo& _Info);

	void CloseStart(const StateInfo& _Info);
	void CloseUpdate(float _DeltaTime, const StateInfo& _Info);

private:
	SteamerState SteamerState_;
	GameEngineStateManager StateManager;

	bool IsInteraction_;
	bool IsMoveDone_;
	bool IsRotateDone_;
	bool IsChangeRot_;
	float Angle_;

	float4 CookingAngle_;
	float4 RandomAngle_;
	float4 CurPos_;
	float4 OpenPos_;

	std::shared_ptr<GameEngineActor> Lid_;
	std::shared_ptr<GameEngineFBXStaticRenderer> LidRenderer_;




	HoldDownEnum PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable) override;
	bool AutoTrim(float _DeltaTime, ObjectToolType _Tool) override;
	// Bowl to Steamer
	bool BowltoSteamer(std::shared_ptr<Equipment_Bowl> _Bowl);
};

