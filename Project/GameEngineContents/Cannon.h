#pragma once
#include "GameEngineCore//GameEngineActor.h"
#include "Player.h"
enum class CannonState
{
	Idle,
	Ready,
	Shoot,
	ShootToIdle,
	Max,
};

// Ό³Έν :

class Cannon : public GameEngineActor
{

public:
	// constrcuter destructer
	Cannon();
	~Cannon();

	// delete Function
	Cannon(const Cannon& _Other) = delete;
	Cannon(Cannon&& _Other) noexcept = delete;
	Cannon& operator=(const Cannon& _Other) = delete;
	Cannon& operator=(Cannon&& _Other) noexcept = delete;

public:
	inline CannonState GetCannonState()
	{
		return CurState_;
	}

	inline void SetCannonState(CannonState _CurState)
	{
		CurState_ = _CurState;
	}
	inline void SetPlayer(std::shared_ptr<Player> _Player)
	{
		CurPlayer_ = _Player;
		CurPlayer_->SetParent(shared_from_this());
	}
	inline void DetachCurPlayer()
	{
		CurPlayer_->DetachObject();
		CurPlayer_ = nullptr;
	}

	inline void SwitchInteraction_()
	{
		Interaction_ = !Interaction_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void ReadyStart(const StateInfo& _Info);
	void ReadyUpdate(float _DeltaTime, const StateInfo& _Info);

	void ShootStart(const StateInfo& _Info);
	void ShootUpdate(float _DeltaTime, const StateInfo& _Info);

	void ShootToIdleStart(const StateInfo& _Info);
	void ShootToIdleUpdate(float _DeltaTime, const StateInfo& _Info);

private:
	std::shared_ptr<GameEngineActor> CannonBase_;
	std::shared_ptr<GameEngineFBXStaticRenderer> Mesh_Object_;
	std::shared_ptr<GameEngineFBXAnimationRenderer> AnimationMesh_Obejct_;
	std::shared_ptr<GameEngineCollision> Collision_Object_;

	std::shared_ptr<Player> CurPlayer_;

	CannonState CurState_;
	GameEngineStateManager StateManager;

	bool Interaction_;
	float4 ZAngle_;
	float4 MaxAngle_;
	float Speed_;
};

