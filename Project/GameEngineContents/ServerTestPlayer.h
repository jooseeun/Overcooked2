#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "GameServerObject.h"

// Ό³Έν :
class GameEngineCollision;
class GameEngineTextureRenderer;
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


protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	static bool OnePlayerInit;

	bool IsPlayerble;

};

