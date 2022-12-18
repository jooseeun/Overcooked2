#include "PreCompile.h"
#include "GameServerObject.h"

std::atomic<int> GameServerObject::IdSeed = 0;
std::map<int, GameServerObject*> GameServerObject::AllServerActor;
std::mutex PacketLock;

void GameServerObject::ServerRelease()
{
	AllServerActor.clear();
}

GameServerObject::GameServerObject()
	: IsNetInit(false)
{
}

GameServerObject::~GameServerObject()
{
}

void GameServerObject::ServerInit(ServerObjectType _Type)
{
	ServerType = _Type;
	ID = GetServerID();

	IsNetInit = true;

	AllServerActor.insert(std::make_pair(ID, this));
}

void GameServerObject::ClientInit(ServerObjectType _Type, int _ID)
{
	ServerType = _Type;
	ID = _ID;

	IsNetInit = true;

	AllServerActor.insert(std::make_pair(ID, this));
}

void GameServerObject::PushPacket(std::shared_ptr<GameServerPacket> _Packet)
{
	std::lock_guard L(PacketLock);
	PacketList.push_back(_Packet);
}

bool GameServerObject::IsPacketEmpty()
{
	std::lock_guard L(PacketLock);
	bool Check = PacketList.empty();
	return Check;
}

std::shared_ptr<GameServerPacket> GameServerObject::PopPacket()
{
	if (PacketList.empty())
	{
		return nullptr;
	}

	std::lock_guard L(PacketLock);
	std::shared_ptr<GameServerPacket> Packet = PacketList.front();
	PacketList.pop_front();
	return Packet;
}
