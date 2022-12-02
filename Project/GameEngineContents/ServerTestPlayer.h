#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "GameServerObject.h"

// Ό³Έν :
class ServerTestPlayer : public GameEngineActor, public GameServerObject
{
private:
	static ServerTestPlayer* MainPlayer;

public:
	static ServerTestPlayer* GetMainPlayer()
	{
		return MainPlayer;
	}

public:
	// constrcuter destructer
	ServerTestPlayer();
	~ServerTestPlayer();

	// delete Function
	ServerTestPlayer(const ServerTestPlayer& _Other) = delete;
	ServerTestPlayer(ServerTestPlayer&& _Other) noexcept = delete;
	ServerTestPlayer& operator=(const ServerTestPlayer& _Other) = delete;
	ServerTestPlayer& operator=(ServerTestPlayer&& _Other) noexcept = delete;

	CollisionReturn MonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	std::shared_ptr<GameEngineTextureRenderer> Renderer_;
	std::shared_ptr<GameEngineCollision> Collision;

	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void MoveUpdate(float _DeltaTime, const StateInfo& _Info);

private:
	static bool OnePlayerInit;

	bool IsPlayerble;

	float Speed;

	float4 ResultColor;

	GameEngineStateManager StateManager;

};

