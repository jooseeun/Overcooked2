#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Enums.h"

// Ό³Έν :
class GameEngineFBXRenderer;
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

	void DashCheck();

	bool MoveAngle();
	float Speed_;
	float CurAngle_;
	PlayerDir CurDir_;
	PlayerDir PreDir_;

private:
	GameEngineFBXRenderer* PlayerRenderer;
	GameEngineStateManager StateManager;
};

