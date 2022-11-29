#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineNetServer.h>
#include <GameEngineBase/GameEngineNetClient.h>

// Ό³Έν :
class ServerTestLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	ServerTestLevel();
	~ServerTestLevel();

	// delete Function
	ServerTestLevel(const ServerTestLevel& _Other) = delete;
	ServerTestLevel(ServerTestLevel&& _Other) noexcept = delete;
	ServerTestLevel& operator=(const ServerTestLevel& _Other) = delete;
	ServerTestLevel& operator=(ServerTestLevel&& _Other) noexcept = delete;

	static GameEngineNet* Net;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	static GameEngineNetServer Server;
	static GameEngineNetClient Client;

};

