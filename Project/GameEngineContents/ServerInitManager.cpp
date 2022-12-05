#include "PreCompile.h"
#include "ServerInitManager.h"
#include "GameEngineStatusWindow.h"
#include "GamePacket.h"
#include "Player.h"

GameServerNet* ServerInitManager::Net;
GameServerNetServer ServerInitManager::Server;
GameServerNetClient ServerInitManager::Client;

ServerInitManager::ServerInitManager()
{
}

ServerInitManager::~ServerInitManager()
{
}

void ServerInitManager::ObjectUpdatePacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	std::shared_ptr<ObjectUpdatePacket> Packet = std::dynamic_pointer_cast<ObjectUpdatePacket>(_Packet);
	if (nullptr == Packet)
	{
		MsgBoxAssert("ObjectUpdate 패킷이 아닙니다");
	}

	std::shared_ptr<GameServerObject> FindObject = GameServerObject::GetServerObject(Packet->ObjectID);
	if (nullptr == FindObject)
	{
		ServerObjectType Type = Packet->Type;
		switch (Type)
		{
		case ServerObjectType::Player:
		{
			std::shared_ptr<Player> NewPlayer = GEngine::GetCurrentLevel()->CreateActor<Player>();
			NewPlayer->GetTransform().SetLocalPosition({ -1400, 500, 200 });
			NewPlayer->ClientInit(Packet->Type, Packet->ObjectID);
			FindObject = NewPlayer;
			break;
		}
		default:
			return;
		}
	}

	FindObject->PushPacket(_Packet);
	if (true == Net->GetIsHost())
	{
		Net->SendPacket(Packet);
	}
}

void ServerInitManager::ClientInitPacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	std::shared_ptr<ClientInitPacket> Packet = std::dynamic_pointer_cast<ClientInitPacket>(_Packet);
	if (nullptr == Packet)
	{
		MsgBoxAssert("ClientInit 패킷이 아닙니다");
	}

	if (true == Net->GetIsHost())
	{
		MsgBoxAssert("호스트인데 클라이언트용 패킷을 받았습니다.");
	}


	//MainPlayer->ClientInit(ServerObjectType::Player, Packet->ObjectID);
}

void ServerInitManager::StartInit()
{
	std::shared_ptr<Player> TmpPlayer;
	if (nullptr == Player::GetMyPlayer())
	{
		TmpPlayer = GEngine::GetCurrentLevel()->CreateActor<Player>();
		Player::SetMyPlayer(TmpPlayer);
		TmpPlayer->SetLevelOverOn();
		TmpPlayer->GetTransform().SetLocalPosition({ -1400, 500, 200 });
	}
	else
	{
		TmpPlayer = Player::GetMyPlayer();
	}

	if (true == GameEngineStatusWindow::IsHost)
	{
		Server.Accept(30001);
		Net = &Server;

		Server.AcceptCallBack = [&](SOCKET _User)
		{
			std::shared_ptr<ClientInitPacket> Packet = std::make_shared<ClientInitPacket>();

			Packet->ObjectID = GameServerObject::GetServerID();

			Server.NetSendPacket(_User, Packet);
		};

		TmpPlayer->ServerInit(ServerObjectType::Player);
	}
	else
	{
		Client.Connect("127.0.0.1", 30001);
		Net = &Client;
	}

	Net->Dis.PacketReturnCallBack = [=](int _PacketType, int _PacketSize, GameServerSerializer& Data)
	{
		ContentsPacketType Type = static_cast<ContentsPacketType>(_PacketType);

		std::shared_ptr<GameServerPacket> NewPacket;

		switch (Type)
		{
		case ContentsPacketType::ObjectUpdate:
			NewPacket = std::make_shared<ObjectUpdatePacket>();
			break;
		case ContentsPacketType::ClinetInit:
			NewPacket = std::make_shared<ClientInitPacket>();
			break;
		default:
			int a = 0;
			break;
		}

		if (NewPacket != nullptr)
		{
			NewPacket->DeSerializePacket(Data);
		}

		return NewPacket;
	};

	Net->Dis.AddHandler(ContentsPacketType::ObjectUpdate, std::bind(&ServerInitManager::ObjectUpdatePacketProcess, this, std::placeholders::_1));

	if (true == Net->GetIsHost())
	{
		// 내가 서버일때만 등록해야하는 패킷
	}
	else
	{
		Net->Dis.AddHandler(ContentsPacketType::ClinetInit, std::bind(&ServerInitManager::ClientInitPacketProcess, this, std::placeholders::_1));
	}
}
