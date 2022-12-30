#pragma once
#include <atomic>
#include <list>
#include "ServerInitManager.h"
#include <mutex>

enum class ServerObjectBaseState
{
	Base,
	Death,
};

enum class ServerObjectType
{
	None = -1,
	Player,
	Object,
	UI
};

// Ό³Έν :
class GameServerObject
{
private:
	static std::atomic<int> IdSeed;
	static std::map<int, GameServerObject*> AllServerActor;

public:
	static void ServerRelease();

	static GameServerObject* GetServerObject(int _ID)
	{
		std::map<int, GameServerObject*>::iterator FindIter = AllServerActor.find(_ID);

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

	inline ServerObjectType GetServerType()
	{
		return ServerType;
	}

protected:

private:
	std::list<std::shared_ptr<GameServerPacket>> PacketList;
	std::mutex Lock_;
	bool IsNetInit;
	ServerObjectType ServerType;
	int ID;
};
