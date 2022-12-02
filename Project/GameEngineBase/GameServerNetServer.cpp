#include "PreCompile.h"
#include "GameServerNetServer.h"
#include "GameEngineString.h"
#include "GameEngineDebug.h"
#include "GameEngineThread.h"
#include "GameServerSerializer.h"

GameServerNetServer::GameServerNetServer()
{
	IsHost = true;
}

GameServerNetServer::~GameServerNetServer()
{
	for (size_t i = 0; i < UserThreads.size(); i++)
	{
		closesocket(UserSockets[i]);
		UserSockets[i] = 0;
		UserThreads[i].Join();
	}

	if (0 != ServerAccpetSocket)
	{
		closesocket(ServerAccpetSocket);
		ServerAccpetSocket = 0;
		AcceptThread.Join();
	}
}

void GameServerNetServer::Accept(int Port)
{
	GameServerNet::WindowNetStartUp();

	SOCKADDR_IN Add;
	Add.sin_family = AF_INET;
	Add.sin_port = htons(Port);

	if (SOCKET_ERROR == inet_pton(AF_INET, "0.0.0.0", &Add.sin_addr))
	{
		return;
	}
	
	ServerAccpetSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == ServerAccpetSocket)
	{
		return;
	}

	if (SOCKET_ERROR == bind(ServerAccpetSocket, (const sockaddr*)&Add, sizeof(SOCKADDR_IN)))
	{
		return;
	}

	if (SOCKET_ERROR == listen(ServerAccpetSocket, 512))
	{
		return;
	}

	AcceptThread.Start("AcceptThread", std::bind(&GameServerNetServer::AcceptFunction, this, &AcceptThread));
}

int GameServerNetServer::SendPacket(std::shared_ptr<GameServerPacket> _Packet)
{
	for (size_t i = 0; i < UserSockets.size(); i++)
	{
		NetSendPacket(UserSockets[i], _Packet);
	}

	return 0;
}

void GameServerNetServer::AcceptFunction(GameEngineThread* Thread)
{
	while (ServerAccpetSocket)
	{
		SOCKADDR_IN UserAddress;
		int AddressLen = sizeof(SOCKADDR_IN);

		SOCKET NewUser = accept(ServerAccpetSocket, (sockaddr*)&UserAddress, &AddressLen);
		if (-1 == NewUser)
		{
			return;
		}

		GameEngineThread& NewThread = UserThreads.emplace_back();
		std::stringstream ThreadName;
		ThreadName << NewUser;
		ThreadName << "UserThread";

		if (nullptr != AcceptCallBack)
		{
			AcceptCallBack(NewUser);
		}

		NewThread.Start(ThreadName.str(), std::bind(&GameServerNetServer::UserFunction, this, &NewThread, NewUser));
		UserSockets.push_back(NewUser);

	}
}

void GameServerNetServer::UserFunction(GameEngineThread* Thread, SOCKET _Socket)
{
	char Packet[1024] = { 0 };

	while (true)
	{
		int Result = recv(_Socket, Packet, sizeof(Packet), 0);

		if (-1 == Result)
		{
			//MsgBoxAssert("네트워크 에러");
			return;
		}

		GameServerSerializer Ser = GameServerSerializer(Packet, 1024);

		int PacketType;
		int PacketSize;

		memcpy_s(&PacketType, sizeof(int), Ser.GetDataPtr(), sizeof(int));
		memcpy_s(&PacketSize, sizeof(int), Ser.GetDataPtr() + 4, sizeof(int));

		std::shared_ptr<GameServerPacket> Packet = Dis.PacketReturnCallBack(PacketType, PacketSize, Ser);
		Dis.ProcessPacket(Packet);
	}
}