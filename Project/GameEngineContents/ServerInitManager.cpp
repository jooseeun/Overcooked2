#include "PreCompile.h"
#include "ServerInitManager.h"
#include "GameEngineStatusWindow.h"
#include "GamePacket.h"
#include "Player.h"
#include "GlobalGameData.h"
#include "GamePlayObject.h"
#include "GamePlayObjectManager.h"

GameServerNet* ServerInitManager::Net;
std::string ServerInitManager::IP = "127.0.0.1";
//std::string ServerInitManager::IP = "10.0.4.94";
GameServerNetServer ServerInitManager::Server;
GameServerNetClient ServerInitManager::Client;

ServerInitManager::ServerInitManager()
{
}

ServerInitManager::~ServerInitManager()
{
}

void ServerInitManager::ObjectCookingGageProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	std::shared_ptr<ObjectCookingGagePacket> Packet = std::dynamic_pointer_cast<ObjectCookingGagePacket>(_Packet);
	GameServerObject* FindObject = GameServerObject::GetServerObject(Packet->ObjectID);
	if (FindObject == nullptr)
	{
		return;
		MsgBoxAssert("Serverinitmanager/ObjectCookingGageProcess() is nullptr")
	}

	FindObject->PushPacket(_Packet);
}

void ServerInitManager::ObjectStartPacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	std::shared_ptr<ObjectStartPacket> Packet = std::dynamic_pointer_cast<ObjectStartPacket>(_Packet);

	GameServerObject* FindObject = GameServerObject::GetServerObject(Packet->ObjectID);

	if (nullptr == FindObject)
	{
		if (GamePlayObjectManager::GetInst() != nullptr)
		{
			GamePlayObjectManager::GetInst()->PushMapData(Packet);
		}
		else
		{
			GamePlayObjectManager::TemporaryPushData(Packet);
		}

		return;
	}

	FindObject->PushPacket(_Packet);
	if (true == Net->GetIsHost())
	{
		Net->SendPacket(Packet);
	}
}

void ServerInitManager::ObjectParentsSetPacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	std::shared_ptr<ObjectParentsSetPacket> Packet = std::dynamic_pointer_cast<ObjectParentsSetPacket>(_Packet);
	GameServerObject* FindObject = GameServerObject::GetServerObject(Packet->ParentsID);
	if (FindObject == nullptr)
	{
		//MsgBoxAssert("아직 등록되지 않은 오브젝트입니다 - Serverinitmanager, ObjectParentsSetPacketProcess()")
		return;
	}

	if (GamePlayObjectManager::GetInst() != nullptr)
	{
		GamePlayObjectManager::GetInst()->PushParentsSetData(Packet);
	}
	else
	{
		GamePlayObjectManager::TemporaryPushData(Packet);
	}
}

void ServerInitManager::ObjectParentsSetAllFramePacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	std::shared_ptr<ObjectParentsSetAllFramePacket> Packet = std::dynamic_pointer_cast<ObjectParentsSetAllFramePacket>(_Packet);
	GameServerObject* FindParentObject = GameServerObject::GetServerObject(Packet->ParentsID);
	GameServerObject* FindChildObject = GameServerObject::GetServerObject(Packet->ChildID);

	if (FindParentObject == nullptr || GamePlayObjectManager::GetInst() == nullptr)
	{
		return;
	}

	if (Packet->ChildID == -1)
	{
		FindParentObject->PushPacket(_Packet);
		return;
	}
	else if (Packet->ChildID <= -2)
	{
		return;
	}

	if (FindChildObject == nullptr)
	{
		GamePlayObjectManager::TemporaryPushData(Packet);
	}
	else
	{
		FindParentObject->PushPacket(_Packet);
	}
}

void ServerInitManager::ObjectInteractUpdateProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	std::shared_ptr<ObjectInteractUpdatePacket> Packet = std::dynamic_pointer_cast<ObjectInteractUpdatePacket>(_Packet);

	GameServerObject* FindObject = GameServerObject::GetServerObject(Packet->ObjectID);
	GameServerObject* FindPlayerObject = GameServerObject::GetServerObject(Packet->PlayerNum);
	if (FindObject == nullptr)
	{
		MsgBoxAssert("아직 등록되지 않은 오브젝트입니다 - Serverinitmanager, ObjectInteractUpdateProcess()")
	}

	if (Packet->PlayerNum < 0)
	{
		MsgBoxAssertString("Serverinitmanager::ObjectInteractUpdateProcess() PlayerNum Is Unknown / " + std::to_string(Packet->PlayerNum))
			return;
	}

	if (FindPlayerObject == nullptr)
	{
		//MsgBoxAssert("아직 등록되지 않은 오브젝트입니다 - Serverinitmanager, ObjectInteractUpdateProcess()")
		GamePlayObjectManager::TemporaryPushData(_Packet);
	}
	else
	{
		FindObject->PushPacket(_Packet);
	}

	//FindObject = GameServerObject::GetServerObject(Packet->PlayerNum);
	//if (FindObject == nullptr)
	//{
	//	MsgBoxAssert("아직 등록되지 않은 오브젝트입니다 - Serverinitmanager, ObjectInteractUpdateProcess()")
	//}
	//FindObject->PushPacket(_Packet);

	if (true == Net->GetIsHost())
	{
		Net->SendPacket(Packet);
	}
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
		else if (ServerObjectType::Cannon == Packet->Type)
		{
			FindObject = GEngine::GetCurrentLevel()->CreateActor<Cannon>().get();
			FindObject->ClientInit(ServerObjectType::Cannon, Packet->ObjectID);
		}

		return;
	}

	if (Packet->State == ServerObjectBaseState::Death)
	{
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
	//GlobalGameData::SetGameStart(true);
}

void ServerInitManager::StartLevelPacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	// 여기에 UI 시작부터 추가하든 하면 됩니다
	//GlobalGameData::SetGameStart(true);
}

void ServerInitManager::UIDataPacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	std::shared_ptr<UIDataPacket> Packet = std::dynamic_pointer_cast<UIDataPacket>(_Packet);

	if (Packet->ObjectID == 3999) //호스트라면 클라이언트 전부에게 전파
	{
		for (int i = 4000;; i++)
		{
			GameServerObject* FindObject = GameServerObject::GetServerObject(i);
			if (FindObject == nullptr)
			{
				return;
			}

			if (FindObject->GetNetID() != i)
			{
				continue;
			}

			FindObject->PushPacket(Packet);
		}
	}
	else //클라면 호스트에게 데이터 전송
	{
		GameServerObject* FindObject = GameServerObject::GetServerObject(3999);
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
		case ContentsPacketType::ObjectCookingGageUpdate:
			NewPacket = std::make_shared<ObjectCookingGagePacket>();
			break;

		case ContentsPacketType::ObjectParentsSet:
			NewPacket = std::make_shared<ObjectParentsSetPacket>();
			break;
		case ContentsPacketType::ObjectStart:
			NewPacket = std::make_shared<ObjectStartPacket>();
			break;
		case ContentsPacketType::ObjectInteractUpdate:
			NewPacket = std::make_shared<ObjectInteractUpdatePacket>();
			break;
		case ContentsPacketType::ObjectParentsSetFrame:
			NewPacket = std::make_shared<ObjectParentsSetAllFramePacket>();
			break;
		case ContentsPacketType::ObjectUpdate:
			NewPacket = std::make_shared<ObjectUpdatePacket>();
			break;
		case ContentsPacketType::UIUpdate:
			NewPacket = std::make_shared<UIDataPacket>();
			break;
		case ContentsPacketType::RecipeTimeUpdate:
			NewPacket = std::make_shared<RecipeTimeUpdatePacket>();
			break;
		case ContentsPacketType::CreateRecipeData:
			NewPacket = std::make_shared<CreateRecipePacket>();
			break;
		case ContentsPacketType::LoadingData:
			NewPacket = std::make_shared<LoadingDataPacket>();
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

	Net->Dis.AddHandler(ContentsPacketType::ObjectStart, std::bind(&ServerInitManager::ObjectStartPacketProcess, std::placeholders::_1));
	Net->Dis.AddHandler(ContentsPacketType::ObjectInteractUpdate, std::bind(&ServerInitManager::ObjectInteractUpdateProcess, std::placeholders::_1));
	Net->Dis.AddHandler(ContentsPacketType::ObjectUpdate, std::bind(&ServerInitManager::ObjectUpdatePacketProcess, std::placeholders::_1));
	Net->Dis.AddHandler(ContentsPacketType::Ignore, std::bind(&ServerInitManager::Ignore, std::placeholders::_1));
	Net->Dis.AddHandler(ContentsPacketType::None, std::bind(&ServerInitManager::Ignore, std::placeholders::_1));
	Net->Dis.AddHandler(ContentsPacketType::StartLevel, std::bind(&ServerInitManager::StartLevelPacketProcess, std::placeholders::_1));
	Net->Dis.AddHandler(ContentsPacketType::LoadingData, std::bind(&ServerInitManager::LoadingDataPacketProcess, std::placeholders::_1));
	Net->Dis.AddHandler(ContentsPacketType::UIUpdate, std::bind(&ServerInitManager::UIDataPacketProcess, std::placeholders::_1));

	if (true == Net->GetIsHost())
	{
		// 내가 서버일때만 등록해야하는 패킷
		Net->Dis.AddHandler(ContentsPacketType::ReadyLevel, std::bind(&ServerInitManager::ReadyLevelPacketProcess, std::placeholders::_1));
	}
	else
	{
		// 내가 클라이언트 일때만 등록해야하는 패킷

		Net->Dis.AddHandler(ContentsPacketType::ObjectParentsSetFrame, std::bind(&ServerInitManager::ObjectParentsSetAllFramePacketProcess, std::placeholders::_1));
		Net->Dis.AddHandler(ContentsPacketType::ObjectCookingGageUpdate, std::bind(&ServerInitManager::ObjectCookingGageProcess, std::placeholders::_1));
		Net->Dis.AddHandler(ContentsPacketType::ObjectParentsSet, std::bind(&ServerInitManager::ObjectParentsSetPacketProcess, std::placeholders::_1));
		Net->Dis.AddHandler(ContentsPacketType::ClinetInit, std::bind(&ServerInitManager::ClientInitPacketProcess, std::placeholders::_1));
		Net->Dis.AddHandler(ContentsPacketType::CreateRecipeData, std::bind(&ServerInitManager::CreateRecipePacketProcess, std::placeholders::_1));
		Net->Dis.AddHandler(ContentsPacketType::ChangeLevel, std::bind(&ServerInitManager::ChangeLevelPacketProcess, std::placeholders::_1));
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