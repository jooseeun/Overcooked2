#include "PreCompile.h"
#include "GameServerNet.h"
#include "GameEngineDebug.h"
#include "GameServerSerializer.h"

GameServerNet::GameServerNet()
{
}

GameServerNet::~GameServerNet()
{
}

void GameServerNet::WindowNetStartUp()
{
	static bool IsStart = false;

	if (true == IsStart)
	{
		return;
	}

	WSAData wsaData;
	int errorCode = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (SOCKET_ERROR == errorCode)
	{
		MsgBoxAssert("winapi server socket startup fail");
		return;
	}

	IsStart = true;
}

int GameServerNet::Send(SOCKET _Socket, const char* Data, size_t _Size)
{
	return send(_Socket, Data, static_cast<int>(_Size), 0);
}

int GameServerNet::Send(const char* Data, size_t _Size)
{
	return 0;
}

GameServerSerializer GameServerNet::PacketSerializ(std::shared_ptr<GameServerPacket> _Packet)
{
	GameServerSerializer NewSer = GameServerSerializer();
	_Packet->SerializePacket(NewSer);
	return NewSer;
}