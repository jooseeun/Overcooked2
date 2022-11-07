#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Enums.h"

// Ό³Έν :
class GameEngineFBXStaticRenderer;
class GameEngineCollision;
class Player : public GameEngineActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void MoveStart(const StateInfo& _Info);
	void MoveUpdate(float _DeltaTime, const StateInfo& _Info);

	void ThrowStart(const StateInfo& _Info);
	void ThrowUpdate(float _DeltaTime, const StateInfo& _Info);

	void HoldStart(const StateInfo& _Info);
	void HoldUpdate(float _DeltaTime, const StateInfo& _Info);

	void SliceStart(const StateInfo& _Info);
	void SliceUpdate(float _DeltaTime, const StateInfo& _Info);

	void DashCheck();

	bool MoveAngle();
	float Speed_;
	float CurAngle_;
	PlayerDir CurDir_;

private:
	GameEngineFBXStaticRenderer* PlayerRenderer_;
	GameEngineCollision* PlayerCollision_;
	GameEngineStateManager StateManager;
};

