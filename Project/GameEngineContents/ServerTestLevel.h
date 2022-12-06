#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameServerNetServer.h>
#include <GameEngineBase/GameServerNetClient.h>
#include <functional>

// Ό³Έν :
class ServerTestPlayer;
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

public:
	void ObjectUpdatePacketProcess(std::shared_ptr<GameServerPacket> _Packet);
	void ClientInitPacketProcess(std::shared_ptr<GameServerPacket> _Packet);

protected:
	void Start() override;
	void LevelStartEvent() override;


	void Update(float _DeltaTime) override {};
	void End() override {};

private:
	std::shared_ptr<ServerTestPlayer> MainPlayer;

	static GameServerNetServer Server;
	static GameServerNetClient Client;

};

