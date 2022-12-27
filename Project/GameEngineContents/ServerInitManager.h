#pragma once
#include <GameEngineBase/GameServerNetServer.h>
#include <GameEngineBase/GameServerNetClient.h>
#include <functional>

// Ό³Έν :
class ServerInitManager
{
public:
	static GameServerNet* Net;
	static std::string IP;

	// constrcuter destructer
	ServerInitManager();
	~ServerInitManager();

	// delete Function
	ServerInitManager(const ServerInitManager& _Other) = delete;
	ServerInitManager(ServerInitManager&& _Other) noexcept = delete;
	ServerInitManager& operator=(const ServerInitManager& _Other) = delete;
	ServerInitManager& operator=(ServerInitManager&& _Other) noexcept = delete;

	static void ObjectUpdatePacketProcess(std::shared_ptr<GameServerPacket> _Packet);
	static void ClientInitPacketProcess(std::shared_ptr<GameServerPacket> _Packet);
	static void Ignore(std::shared_ptr<GameServerPacket> _Packet);
	static void ChangeLevelPacketProcess(std::shared_ptr<GameServerPacket> _Packet);
	static void ReadyLevelPacketProcess(std::shared_ptr<GameServerPacket> _Packet);
	static void StartLevelPacketProcess(std::shared_ptr<GameServerPacket> _Packet);
	static void UIDataPacketProcess(std::shared_ptr<GameServerPacket> _Packet);
	static void LoadingDataPacketProcess(std::shared_ptr<GameServerPacket> _Packet);

	static void StartInit();
	static void Update(float _Delta);

private:
	static GameServerNetServer Server;
	static GameServerNetClient Client;
};
