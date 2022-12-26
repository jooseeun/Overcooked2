#include "PreCompile.h"
#include "ServerInitManager.h"
#include "GameEngineStatusWindow.h"
#include "GamePacket.h"
#include "Player.h"
#include "GlobalGameData.h"

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
		MsgBoxAssert("클라이언트 init패킷이 아닙니다");
	}

	if (true == Net->GetIsHost())
	{
		MsgBoxAssert("호스트인데 클라이언트용 패킷을 받았습니다.");
	}

	Player::GetMyPlayer()->ClientInit(ServerObjectType::Player, Packet->ObjectID);
}

void ServerInitManager::Ignore(std::shared_ptr<GameServerPacket> _Packet)
{
	return;
}

void ServerInitManager::ChangeLevelPacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	std::shared_ptr<ChangeLevelPacket> Packet = std::dynamic_pointer_cast<ChangeLevelPacket>(_Packet);
	std::string& NextLevelName = Packet->LevelName;
	GEngine::ChangeLevel(NextLevelName);
}

void ServerInitManager::ReadyLevelPacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	if (false == Net->GetIsHost())
	{
		return;
	}

	std::vector<SOCKET>& AllSockets = Server.GetUserSockets();
	std::vector<bool>& AllReadys = Server.GetReadyLevels();
	if (AllSockets.size() <= 0)
	{
		return;
	}

	for (size_t i = 0; i < AllSockets.size(); i++)
	{
		if (AllSockets[i] == _Packet->GetMaster())
		{
			AllReadys[i] = true;
		}
	}

	for (size_t i = 0; i < AllReadys.size(); i++)
	{
		if (AllReadys[i] == false)
		{
			return;
		}
	}

	std::shared_ptr<IgnorePacket> Packet = std::make_shared<IgnorePacket>();
	Packet->SetPacketID(ContentsPacketType::StartLevel);
	ServerInitManager::Net->SendPacket(Packet);
	GlobalGameData::SetGameStart(true);
}

void ServerInitManager::StartLevelPacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	// 여기에 UI 시작부터 추가하든 하면 됩니다
	GlobalGameData::SetGameStart(true);
}

void ServerInitManager::UIDataPacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	std::shared_ptr<UIDataPacket> Packet = std::dynamic_pointer_cast<UIDataPacket>(_Packet);

	for (int i = 4000;; i++)
	{
		GameServerObject* FindObject = GameServerObject::GetServerObject(i);
		if (FindObject == nullptr)
		{
			return;
		}

		FindObject->PushPacket(Packet);
	}
	//GameServerObject* FindObject = GameServerObject::GetServerObject(0);

//	FindObject->PushPacket(_Packet);
	//if (true == Net->GetIsHost())
	//{
	//	Net->SendPacket(Packet);
	//}
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
		case ContentsPacketType::UIUpdate:
			NewPacket = std::make_shared<UIDataPacket>();
			break;
		case ContentsPacketType::ClinetInit:
			NewPacket = std::make_shared<ClientInitPacket>();
			break;
		case ContentsPacketType::ChangeLevel:
			NewPacket = std::make_shared<ChangeLevelPacket>();
			break;
		case ContentsPacketType::ReadyLevel:
			NewPacket = std::make_shared<IgnorePacket>();
			NewPacket->SetPacketID(ContentsPacketType::ReadyLevel);
			break;
		case ContentsPacketType::StartLevel:
			NewPacket = std::make_shared<IgnorePacket>();
			NewPacket->SetPacketID(ContentsPacketType::StartLevel);
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
	Net->Dis.AddHandler(ContentsPacketType::StartLevel, std::bind(&ServerInitManager::StartLevelPacketProcess, std::placeholders::_1));

	if (true == Net->GetIsHost())
	{
		// 내가 서버일때만 등록해야하는 패킷
		Net->Dis.AddHandler(ContentsPacketType::ReadyLevel, std::bind(&ServerInitManager::ReadyLevelPacketProcess, std::placeholders::_1));
	}
	else
	{
		// 내가 클라이언트 일때만 등록해야하는 패킷
		Net->Dis.AddHandler(ContentsPacketType::ClinetInit, std::bind(&ServerInitManager::ClientInitPacketProcess, std::placeholders::_1));
		Net->Dis.AddHandler(ContentsPacketType::ChangeLevel, std::bind(&ServerInitManager::ChangeLevelPacketProcess, std::placeholders::_1));
		Net->Dis.AddHandler(ContentsPacketType::UIUpdate, std::bind(&ServerInitManager::UIDataPacketProcess, std::placeholders::_1));
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
				NewPlayer->GetTransform().SetLocalPosition({ 0, 0, 0 });
				NewPlayer->SetLevelOverOn();
			}
		}
	}
}