#pragma once
#include "GamePlayBowl.h"

enum class SteamerState
{
	Idle,		// À½½Ä ³ÖÀ» ¼ö ÀÖ´Â »óÅÂ + ¿­·Á ÀÖÀ½
	Cooking,	// ¿ä¸®Áß
	Opening,	// ¶Ñ²± ´ÝÈ÷´Â ¿­¸®´Â ¾Ö´Ï¸ÞÀÌ¼Ç
	Closing,	// ¶Ñ²± ´ÝÈ÷´Â ¾Ö´Ï¸ÞÀÌ¼Ç
	Closed,		// Cooker¿¡¼­ ¶³¾îÁ³À» ¶§, ¶Ñ²± ´ÝÈù Ã¤·Î ¸ØÃçÀÖ´Â »óÅÂ
	Max,
};

// ¼³¸í :
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

	inline void SwitchInteractionOff()
	{
		IsInteraction_ = false;
	}

	inline void SwitchInteractionOn()
	{
		IsInteraction_ = true;
	}

	inline void ChangeToClosedState()
	{
		StateManager.ChangeState("Closed");
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void OpeningStart(const StateInfo& _Info);
	void OpeningUpdate(float _DeltaTime, const StateInfo& _Info);

	void CookingStart(const StateInfo& _Info);
	void CookingUpdate(float _DeltaTime, const StateInfo& _Info);

	void ClosingStart(const StateInfo& _Info);
	void ClosingUpdate(float _DeltaTime, const StateInfo& _Info);

	void ClosedStart(const StateInfo& _Info);
	void ClosedUpdate(float _DeltaTime, const StateInfo& _Info);

private:
	SteamerState SteamerState_;
	GameEngineStateManager StateManager;

	bool IsInteraction_;
	bool IsMoveDone_;
	bool IsRotateDone_;
	bool IsChangeRot_;
	bool IsCookingSound_;
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

