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
		UserThreads[i]->Join();
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
	Add.sin_family = AF_INET; // ip4 林家

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

		std::shared_ptr<GameEngineThread> NewThread = std::make_shared<GameEngineThread>();
		UserThreads.push_back(NewThread);
		std::stringstream ThreadName;
		ThreadName << NewUser;
		ThreadName << "UserThread";

		if (nullptr != AcceptCallBack)
		{
			AcceptCallBack(NewUser);
		}

		UserSockets.push_back(NewUser);
		ReadyLevels.push_back(false);
		NewThread->Start(ThreadName.str(), std::bind(&GameServerNetServer::UserFunction, this, NewThread.get(), NewUser));
	}
}

void GameServerNetServer::UserFunction(GameEngineThread* Thread, SOCKET _Socket)
{
	char Packet[1024] = { 0 };
	std::vector<char> PacketVector;

	while (true)
	{
		int Result = recv(_Socket, Packet, sizeof(Packet), 0);

		if (-1 == Result)
		{
			//MsgBoxAssert("匙飘况农 俊矾");
			return;
		}

		size_t PrevSize = PacketVector.size();

		PacketVector.resize(PacketVector.size() + Result);

		memcpy_s(&PacketVector[PrevSize], PacketVector.size() - PrevSize, Packet, Result);

		while (true)
		{
			if (8 >= PacketVector.size())
			{
				break;
			}

			int PacketType;
			int PacketSize;
			memcpy_s(&PacketType, sizeof(int), &PacketVector[0], sizeof(int));
			memcpy_s(&PacketSize, sizeof(int), &PacketVector[4], sizeof(int));

			if (PacketVector.size() < PacketSize)
			{
				break;
			}

			GameServerSerializer Ser = GameServerSerializer(&PacketVector[0], PacketSize);

			std::shared_ptr<GameServerPacket> Packet = Dis.PacketReturnCallBack(PacketType, PacketSize, Ser);
			Packet->SetMaster(_Socket);
			Dis.ProcessPacket(Packet);

			GameEngineDebug::OutPutString("Recv Server : " + std::to_string(PacketType) + ", " + std::to_string(PacketSize));

			if (PacketVector.size() > PacketSize)
			{
				memcpy_s(&PacketVector[0], PacketVector.size(), &PacketVector[PacketSize], PacketVector.size() - PacketSize);
			}

			PacketVector.resize(PacketVector.size() - PacketSize);
		}
	}
}


int GameServerNetServer::SendPacket(std::shared_ptr<GameServerPacket> _Packet)
{
	for (size_t i = 0; i < UserSockets.size(); i++)
	{
		if (UserSockets[i] == _Packet->GetMaster())
		{
			continue;
		}

		NetSendPacket(UserSockets[i], _Packet);
	}

	GameEngineDebug::OutPutString("Send Server : " + std::to_string(_Packet->GetPacketID()) + ", " + std::to_string(_Packet->GetPacketSize()));

	return 0;
}
