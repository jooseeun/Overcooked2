#pragma once
#include <GameEngineBase/GameServerNetServer.h>
#include <GameEngineBase/GameServerNetClient.h>

// Ό³Έν :
class ServerInitManager
{
public:
	static GameServerNet* Net;
	
	// constrcuter destructer
	ServerInitManager();
	~ServerInitManager();

	// delete Function
	ServerInitManager(const ServerInitManager& _Other) = delete;
	ServerInitManager(ServerInitManager&& _Other) noexcept = delete;
	ServerInitManager& operator=(const ServerInitManager& _Other) = delete;
	ServerInitManager& operator=(ServerInitManager&& _Other) noexcept = delete;

	void ObjectUpdatePacketProcess(std::shared_ptr<GameServerPacket> _Packet);
	void ClientInitPacketProcess(std::shared_ptr<GameServerPacket> _Packet);

protected:
	void StartInit();

private:
	bool IsLevelFirst_ = true;

	static GameServerNetServer Server;
	static GameServerNetClient Client;

};

