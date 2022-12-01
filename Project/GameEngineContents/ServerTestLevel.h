#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameServerNetServer.h>
#include <GameEngineBase/GameServerNetClient.h>

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

	static GameServerNet* Net;
	void ObjectUpdatePacketProcess(std::shared_ptr<GameServerPacket> _Packet);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	static GameServerNetServer Server;
	static GameServerNetClient Client;

	std::map<__int64, std::shared_ptr<GameEngineActor>> AllServerActor;

};

