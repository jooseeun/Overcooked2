#pragma once
#include <GameEngineBase/GameServerNetServer.h>
#include <GameEngineBase/GameServerNetClient.h>
#include <functional>

// 설명 :
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

	static void ObjectInteractUpdateProcess(std::shared_ptr<GameServerPacket> _Packet);
	static void ObjectParentsSetPacketProcess(std::shared_ptr<GameServerPacket> _Packet);
	static void ObjectParentsSetAllFramePacketProcess(std::shared_ptr<GameServerPacket> _Packet);
	static void ObjectCookingGageProcess(std::shared_ptr<GameServerPacket> _Packet);

	static void ObjectStartPacketProcess(std::shared_ptr<GameServerPacket> _Packet);
	static void ObjectUpdatePacketProcess(std::shared_ptr<GameServerPacket> _Packet);
	static void ClientInitPacketProcess(std::shared_ptr<GameServerPacket> _Packet);
	static void Ignore(std::shared_ptr<GameServerPacket> _Packet);
	static void ChangeLevelPacketProcess(std::shared_ptr<GameServerPacket> _Packet);
	static void ReadyLevelPacketProcess(std::shared_ptr<GameServerPacket> _Packet);
	static void StartLevelPacketProcess(std::shared_ptr<GameServerPacket> _Packet);
	static void UIDataPacketProcess(std::shared_ptr<GameServerPacket> _Packet);
	static void LoadingDataPacketProcess(std::shared_ptr<GameServerPacket> _Packet);
	static void CreateRecipePacketProcess(std::shared_ptr<GameServerPacket> _Packet);	// Host to Client  :  호스트가 레시피를 만들 때 동일한 레시피 생성을 명령
	static void SelectStageInputDataPacketProcess(std::shared_ptr<GameServerPacket> _Packet); // Host to Client : 입력한 키 데이터 전달

	static void StartInit();
	static void Update(float _Delta);

	static GameServerNetServer Server;
private:
	static GameServerNetClient Client;
};
