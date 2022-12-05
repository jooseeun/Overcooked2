#pragma once
#include <atomic>
#include <list>
#include "ServerInitManager.h"

enum class ServerObjectBaseState
{
	Base,
	Death,
};

enum class ServerObjectType
{
	Player,
};

// ���� :
class GameServerObject
{
private:
	static std::atomic<int> IdSeed;
	static std::map<int, std::shared_ptr<GameServerObject>> AllServerActor;

public:
	static std::shared_ptr<GameServerObject> GetServerObject(int _ID)
	{
		std::map<int, std::shared_ptr<GameServerObject>>::iterator FindIter = AllServerActor.find(_ID);

		if (FindIter == AllServerActor.end())
		{
			return nullptr;
		}

		return FindIter->second;
	}

public:
	static int GetServerID()
	{
		return ++IdSeed;
	}

public:
	// constrcuter destructer
	GameServerObject(/*ServerObjectType _Type*/);
	~GameServerObject();

	// delete Function
	GameServerObject(const GameServerObject& _Other) = delete;
	GameServerObject(GameServerObject&& _Other) noexcept = delete;
	GameServerObject& operator=(const GameServerObject& _Other) = delete;
	GameServerObject& operator=(GameServerObject&& _Other) noexcept = delete;

	void ServerInit(ServerObjectType _Type);
	void ClientInit(ServerObjectType _Type, int _ID);

	bool GetIsNetInit()
	{
		return IsNetInit;
	}

	int GetNetID()
	{
		return ID;
	}

	void PushPacket(std::shared_ptr<GameServerPacket> _Packet);
	bool IsPacketEmpty();
	std::shared_ptr<GameServerPacket> PopPacket();

protected:

private:
	std::list<std::shared_ptr<GameServerPacket>> PacketList;
	bool IsNetInit;
	ServerObjectType ServerType;
	int ID;

};

