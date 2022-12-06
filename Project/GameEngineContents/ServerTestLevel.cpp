#include "PreCompile.h"
#include "ServerTestLevel.h"

#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineCore/GameEngineInstancing.h>
#include <GameEngineBase/GameEngineInput.h>
#include "GameEngineStatusWindow.h"

#include <GameEngineCore/GameEngineBlur.h>
#include "ServerTestPlayer.h"
#include "GamePacket.h"

GameServerNet* ServerTestLevel::Net;

GameServerNetServer ServerTestLevel::Server;
GameServerNetClient ServerTestLevel::Client;

ServerTestLevel::ServerTestLevel()
{
}

ServerTestLevel::~ServerTestLevel()
{
}

void ServerTestLevel::Start()
{
	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
}

void ServerTestLevel::ObjectUpdatePacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	std::shared_ptr<ObjectUpdatePacket> Packet = std::dynamic_pointer_cast<ObjectUpdatePacket>(_Packet);

	GameServerObject* FindObject = GameServerObject::GetServerObject(Packet->ObjectID);

	if (nullptr == FindObject)
	{
		ServerObjectType Type = Packet->Type;
		switch (Type)
		{
		case ServerObjectType::Player:
		{
			std::shared_ptr<ServerTestPlayer> NewPlayer = CreateActor<ServerTestPlayer>();
			NewPlayer->ClientInit(Packet->Type, Packet->ObjectID);
			FindObject = NewPlayer.get();
			break;
		}
		default:
			break;
		}
	}

	FindObject->PushPacket(_Packet);
	if (true == Net->GetIsHost())
	{
		ServerTestLevel::Net->SendPacket(Packet);
	}
}

void ServerTestLevel::ClientInitPacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	std::shared_ptr<ClientInitPacket> Packet = std::dynamic_pointer_cast<ClientInitPacket>(_Packet);
	if (nullptr == Packet)
	{
		MsgBoxAssert("클라이언트 init패킷이 아닙니다");
	}

	if (true == Net->GetIsHost())
	{
		MsgBoxAssert("호스인데 클라이언트용 패킷을 받았습니다.");
	}

	MainPlayer->ClientInit(ServerObjectType::Player, Packet->ObjectID);
}

void ServerTestLevel::LevelStartEvent()
{
	{
		if (nullptr == ServerTestPlayer::GetMainPlayer())
		{
			MainPlayer = CreateActor<ServerTestPlayer>();
			MainPlayer->SetLevelOverOn();
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

			MainPlayer->ServerInit(ServerObjectType::Player);
		}
		else
		{
			// "127.0.0.1" 인터넷 통신 규약의 약속으로
			// 이 번호는 localhost
			// 나한테 접속하겠다.
			// Client.Connect("127.0.0.1", 30222);

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

			NewPacket->DeSerializePacket(Data);

			return NewPacket;
		};

		// std::function<void(std::shared_ptr<GameServerPacket>)> CallBack = std::bind(&ServerLevel::ObjectUpdatePacketProcess, this,std::placeholders::_1);

		// 공통 패킷
		Net->Dis.AddHandler(ContentsPacketType::ObjectUpdate, std::bind(&ServerTestLevel::ObjectUpdatePacketProcess, this, std::placeholders::_1));

		if (true == Net->GetIsHost())
		{
			// 내가 서버일때만 등록해야하는 패킷
		}
		else
		{
			// 내가 클라이언트 일때만 등록해야하는 패킷
			Net->Dis.AddHandler(ContentsPacketType::ClinetInit, std::bind(&ServerTestLevel::ClientInitPacketProcess, this, std::placeholders::_1));
		}


	}
}


void ServerTestLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDownKey("FreeCameaOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}
}
void ServerTestLevel::End() {}


