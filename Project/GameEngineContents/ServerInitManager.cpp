#include "PreCompile.h"
#include "ServerInitManager.h"
#include "GameEngineStatusWindow.h"
#include "GamePacket.h"
#include "Player.h"

GameServerNet* ServerInitManager::Net;
std::string ServerInitManager::IP = "127.0.0.1";
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

	GameServerObject* FindObject = GameServerObject::GetServerObject(Packet->ObjectID);

	if (nullptr == FindObject)
	{
		if (ServerObjectType::Player == Packet->Type)
		{
			if (Player::MaxPlayerCount_ < Packet->ObjectID)
			{
				Player::MaxPlayerCount_ = Packet->ObjectID;
			}
		}

		return;
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
		MsgBoxAssert("Ŭ���̾�Ʈ init��Ŷ�� �ƴմϴ�");
	}

	if (true == Net->GetIsHost())
	{
		MsgBoxAssert("ȣ��Ʈ�ε� Ŭ���̾�Ʈ�� ��Ŷ�� �޾ҽ��ϴ�.");
	}

	Player::GetMyPlayer()->ClientInit(ServerObjectType::Player, Packet->ObjectID);
}

void ServerInitManager::Ignore(std::shared_ptr<GameServerPacket> _Packet)
{
	return;
}

void ServerInitManager::StartInit()
{
	if (Player::GetMyPlayer() == nullptr)
	{
		GEngine::GetCurrentLevel()->CreateActor<Player>();
		Player::GetMyPlayer()->SetLevelOverOn();
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

		Player::GetMyPlayer()->CastThis<GameServerObject>()->ServerInit(ServerObjectType::Player);
	}
	else
	{
		Client.Connect(IP, 30001);
		Net = &Client;
	}

	Net->Dis.PacketReturnCallBack = [=](int _PacketType, int _PacketSize, GameServerSerializer& Data)
	{
		std::shared_ptr<GameServerPacket> NewPacket;
		ContentsPacketType Type = static_cast<ContentsPacketType>(_PacketType);
		switch (Type)
		{
		case ContentsPacketType::ObjectUpdate:
			NewPacket = std::make_shared<ObjectUpdatePacket>();
			break;
		case ContentsPacketType::ClinetInit:
			NewPacket = std::make_shared<ClientInitPacket>();
			break;
		default:
			NewPacket = std::make_shared<IgnorePacket>();
			break;
		}

		NewPacket->DeSerializePacket(Data);
		return NewPacket;
	};

	Net->Dis.AddHandler(ContentsPacketType::ObjectUpdate, std::bind(&ServerInitManager::ObjectUpdatePacketProcess, std::placeholders::_1));
	Net->Dis.AddHandler(ContentsPacketType::Ignore, std::bind(&ServerInitManager::Ignore, std::placeholders::_1));
	Net->Dis.AddHandler(ContentsPacketType::None, std::bind(&ServerInitManager::Ignore, std::placeholders::_1));

	if (true == Net->GetIsHost())
	{
		// ���� �����϶��� ����ؾ��ϴ� ��Ŷ
		//Net->Dis.AddHandler(ContentsPacketType::ClinetInit, std::bind(&ServerInitManager::Ignore, std::placeholders::_1));
	}
	else
	{
		// ���� Ŭ���̾�Ʈ �϶��� ����ؾ��ϴ� ��Ŷ
		Net->Dis.AddHandler(ContentsPacketType::ClinetInit, std::bind(&ServerInitManager::ClientInitPacketProcess, std::placeholders::_1));
	}
}

void ServerInitManager::Update(float _Delta)
{
	if (nullptr == Net)
	{
		return;
	}

	if (Player::MaxPlayerCount_ > Player::PlayerCount_)
	{
		for (int i = 0; i < Player::MaxPlayerCount_; i++)
		{
			if (nullptr == GameServerObject::GetServerObject(i + 1))
			{
				std::shared_ptr<Player> NewPlayer = GEngine::GetCurrentLevel()->CreateActor<Player>();
				NewPlayer->ClientInit(ServerObjectType::Player, i + 1);
				NewPlayer->GetTransform().SetLocalPosition({ -1400, 500, 200 });
				NewPlayer->SetLevelOverOn();
			}
		}
	}
}
