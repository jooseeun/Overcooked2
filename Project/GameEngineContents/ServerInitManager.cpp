#include "PreCompile.h"
#include "ServerInitManager.h"
#include "GameEngineStatusWindow.h"
#include "GamePacket.h"
#include "Player.h"
#include "GlobalGameData.h"
#include "GamePlayObject.h"

#include "MapDataParser.h"
#include "GamePlayOriginObject.h"
#include "GamePlayMapObject.h"

#include "CounterTop.h"
#include "TrashCan.h"
#include "Servicehatch.h"
#include "PlateReturn.h"
#include "Cooker.h"
#include "Sink.h"
#include "FoodBox.h"
#include "Rail.h"
#include "Dispenser.h"
#include "Cannon.h"
#include "Button.h"
#include "Oven.h"

#include "Equipment_Plate.h"
#include "Equipment_FireExtinguisher.h"
#include "Equipment_FryingPan.h"
#include "Equipment_Pot.h"
#include "Tool_CuttingBoard.h"
#include "Equipment_Bowl.h"
#include "Equipment_Steamer.h"
#include "Mixer.h"


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


void ServerInitManager::ObjectStartPacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	std::shared_ptr<ObjectStartPacket> Packet = std::dynamic_pointer_cast<ObjectStartPacket>(_Packet);

	GameServerObject* FindObject = GameServerObject::GetServerObject(Packet->ObjectID);

	if (nullptr == FindObject)
	{
		if (ServerObjectType::Object == Packet->Type)
		{
			std::shared_ptr<GamePlayObject> PlayObject;

			if (Packet->MapObjData != MapObjType::Max)
			{
				std::weak_ptr<GamePlayStaticObject> CurActor_;
				switch (Packet->MapObjData)
				{
				case MapObjType::CounterTop:
				{
					CurActor_ = GEngine::GetCurrentLevel()->CreateActor<CounterTop>();
					std::weak_ptr<CounterTop> Object = std::dynamic_pointer_cast<CounterTop>(CurActor_.lock());

					Object.lock()->SetCounterTopType(CounterTopType::Normal);
					Object.lock()->SetConterTopMesh(CounterTopType::Normal);
				}
				break;
				case MapObjType::CounterTop_Corner:
				{
					CurActor_ = GEngine::GetCurrentLevel()->CreateActor<CounterTop>();
					std::weak_ptr<CounterTop> Object = std::dynamic_pointer_cast<CounterTop>(CurActor_.lock());

					Object.lock()->SetCounterTopType(CounterTopType::Corner);
					Object.lock()->SetConterTopMesh(CounterTopType::Corner);

					Object.lock()->SetStaticObjectType(MapObjType::CounterTop_Corner);
				}
				break;
				case MapObjType::CounterTop_NoEdge:
				{
					CurActor_ = GEngine::GetCurrentLevel()->CreateActor<CounterTop>();
					std::weak_ptr<CounterTop> Object = std::dynamic_pointer_cast<CounterTop>(CurActor_.lock());

					Object.lock()->SetCounterTopType(CounterTopType::NoEdge);
					Object.lock()->SetConterTopMesh(CounterTopType::NoEdge);

					Object.lock()->SetStaticObjectType(MapObjType::CounterTop_NoEdge);
				}
				break;
				case MapObjType::CounterTop_WiZard:
				{
					CurActor_ = GEngine::GetCurrentLevel()->CreateActor<CounterTop>();
					std::weak_ptr<CounterTop> Object = std::dynamic_pointer_cast<CounterTop>(CurActor_.lock());

					Object.lock()->SetCounterTopType(CounterTopType::Wizard);
					Object.lock()->SetConterTopMesh(CounterTopType::Wizard);

					Object.lock()->SetStaticObjectType(MapObjType::CounterTop_WiZard);
				}
				break;
				case MapObjType::CounterTop_Winter:
				{
					CurActor_ = GEngine::GetCurrentLevel()->CreateActor<CounterTop>();
					std::weak_ptr<CounterTop> Object = std::dynamic_pointer_cast<CounterTop>(CurActor_.lock());

					Object.lock()->SetCounterTopType(CounterTopType::Winter);
					Object.lock()->SetConterTopMesh(CounterTopType::Winter);

					Object.lock()->SetStaticObjectType(MapObjType::CounterTop_Winter);
				}
				break;
				case MapObjType::Mixer_Kevin:
				{
					CurActor_ = GEngine::GetCurrentLevel()->CreateActor<Mixer>();
					std::weak_ptr<Mixer> Object = std::dynamic_pointer_cast<Mixer>(CurActor_.lock());

					Object.lock()->SetMixerType(MixerType::Mixer_Kevin);
					Object.lock()->SetMixerMesh(MixerType::Mixer_Kevin);
				}
				break;
				case MapObjType::Mixer_Winter:
				{
					CurActor_ = GEngine::GetCurrentLevel()->CreateActor<Mixer>();
					std::weak_ptr<Mixer> Object = std::dynamic_pointer_cast<Mixer>(CurActor_.lock());

					Object.lock()->SetMixerType(MixerType::Mixer_Winter);
					Object.lock()->SetMixerMesh(MixerType::Mixer_Winter);

					Object.lock()->SetStaticObjectType(MapObjType::Mixer_Winter);
				}
				break;
				case MapObjType::Cooker:
				{
					CurActor_ = GEngine::GetCurrentLevel()->CreateActor<Cooker>();

				}
				break;
				case MapObjType::TrashCan:
				{
					CurActor_ = GEngine::GetCurrentLevel()->CreateActor<TrashCan>();
					CurActor_.lock()->SetStaticObjectType(MapObjType::TrashCan);
				}
				break;
				case MapObjType::Sink:
				{
					CurActor_ = GEngine::GetCurrentLevel()->CreateActor<Sink>();
					CurActor_.lock()->SetStaticObjectType(MapObjType::Sink);
					std::weak_ptr<Sink> Object = std::dynamic_pointer_cast<Sink>(CurActor_.lock());
					Object.lock()->SetSinkMesh(SinkType::Normal);
				}
				break;
				case MapObjType::Servicehatch:
				{
					CurActor_ = GEngine::GetCurrentLevel()->CreateActor<Servicehatch>();
					CurActor_.lock()->SetStaticObjectType(MapObjType::Servicehatch);
				}
				break;
				case MapObjType::PlateReturn:
				{
					CurActor_ = GEngine::GetCurrentLevel()->CreateActor<PlateReturn>();
					CurActor_.lock()->SetStaticObjectType(MapObjType::PlateReturn);
				}
				break;
				case MapObjType::FoodBox_Normal:
				{
					CurActor_ = GEngine::GetCurrentLevel()->CreateActor<FoodBox>();
					CurActor_.lock()->SetStaticObjectType(MapObjType::FoodBox_Normal);

					std::weak_ptr<FoodBox> Object = std::dynamic_pointer_cast<FoodBox>(CurActor_.lock());
					Object.lock()->SetFoodBoxMesh(FoodBoxType::Normal);
					Object.lock()->SetFoodType(Packet->IngredientData);
				}
				break;
				case MapObjType::FoodBox_Winter:
				{
					CurActor_ = GEngine::GetCurrentLevel()->CreateActor<FoodBox>();
					CurActor_.lock()->SetStaticObjectType(MapObjType::FoodBox_Winter);

					std::weak_ptr<FoodBox> Object = std::dynamic_pointer_cast<FoodBox>(CurActor_.lock());
					Object.lock()->SetFoodBoxMesh(FoodBoxType::Winter);
					Object.lock()->SetFoodType(Packet->IngredientData);
				}
				break;
				case MapObjType::Sink_Wizard:
				{
					CurActor_ = GEngine::GetCurrentLevel()->CreateActor<Sink>();
					CurActor_.lock()->SetStaticObjectType(MapObjType::Sink_Wizard);

					std::weak_ptr<Sink> Object = std::dynamic_pointer_cast<Sink>(CurActor_.lock());
					Object.lock()->SetSinkMesh(SinkType::Wizard);
				}
				break;
				case MapObjType::Rail:
				{
					CurActor_ = GEngine::GetCurrentLevel()->CreateActor<Rail>();
					CurActor_.lock()->SetStaticObjectType(MapObjType::Rail);
				}
				break;
				case MapObjType::Dispenser_Type1:
				{
					CurActor_ = GEngine::GetCurrentLevel()->CreateActor<Dispenser>();
					std::weak_ptr<Dispenser> Object = std::dynamic_pointer_cast<Dispenser>(CurActor_.lock());

					Object.lock()->SetDispenserType(DispenserType::Type1);
					Object.lock()->SettingIngredientList(DispenserType::Type1);
					Object.lock()->SetStaticObjectType(MapObjType::Dispenser_Type1);
				}
				break;
				case MapObjType::Dispenser_Type2:
				{
					CurActor_ = GEngine::GetCurrentLevel()->CreateActor<Dispenser>();
					std::weak_ptr<Dispenser> Object = std::dynamic_pointer_cast<Dispenser>(CurActor_.lock());

					Object.lock()->SetDispenserType(DispenserType::Type2);
					Object.lock()->SettingIngredientList(DispenserType::Type2);
					Object.lock()->SetStaticObjectType(MapObjType::Dispenser_Type2);
				}
				break;
				case MapObjType::Oven:
				{
					CurActor_ = GEngine::GetCurrentLevel()->CreateActor<Oven>();
					CurActor_.lock()->SetStaticObjectType(MapObjType::Oven);
				}
				break;
				default:
					break;
				}
				PlayObject = CurActor_.lock();
			}
			else if (Packet->ToolData != ToolInfo::None)
			{
				switch (Packet->ToolData)
				{
				case ToolInfo::Plate:
				{
					//부모로 둔다
					std::weak_ptr<Equipment_Plate> Plate = GEngine::GetCurrentLevel()->CreateActor<Equipment_Plate>();
					PlayObject = Plate.lock();
				}
				break;
				case ToolInfo::FireExtinguisher:
				{
					std::weak_ptr<Equipment_FireExtinguisher> FireExtinguisher = GEngine::GetCurrentLevel()->CreateActor<Equipment_FireExtinguisher>();
					PlayObject = FireExtinguisher.lock();
				}
				break;
				case ToolInfo::FryingPan:
				{
					std::weak_ptr<Equipment_FryingPan> FryingPan = GEngine::GetCurrentLevel()->CreateActor<Equipment_FryingPan>();
					PlayObject = FryingPan.lock();
				}
				break;
				case ToolInfo::Pot:
				{
					std::weak_ptr<Equipment_Pot> Pot = GEngine::GetCurrentLevel()->CreateActor<Equipment_Pot>();
					PlayObject = Pot.lock();
				}
				break;
				case ToolInfo::CuttingBoard:
				{
					std::weak_ptr<Tool_CuttingBoard> CuttingBoard = GEngine::GetCurrentLevel()->CreateActor<Tool_CuttingBoard>();
					PlayObject = CuttingBoard.lock();
				}
				break;
				case ToolInfo::Bowl:
				{
					std::weak_ptr<Equipment_Bowl> Bowl = GEngine::GetCurrentLevel()->CreateActor<Equipment_Bowl>();
					PlayObject = Bowl.lock();
				}
				break;
				case ToolInfo::Steamer:
				{
					std::weak_ptr<Equipment_Steamer> Steamer = GEngine::GetCurrentLevel()->CreateActor<Equipment_Steamer>();
					PlayObject = Steamer.lock();
				}
				break;
				}

			}
			else if (Packet->IngredientData != IngredientType::None)
			{

			}
			else
			{
				MsgBoxAssert("ServerInitManager 처리할수 없는 Object 데이터")
			}
			PlayObject->ClientInit(ServerObjectType::Object, Packet->ObjectID);

			//if (Packet->Pos.CompareInt3D(float4::ZERO))
			//{

			//}
			PlayObject->GetTransform().SetWorldPosition(Packet->Pos);
			PlayObject->GetTransform().SetWorldRotation(Packet->Rot);
			PlayObject->GetTransform().SetWorldScale(Packet->Scale);

			GamePlayObject::ObjectNumber_ = Packet->ObjectID;

			if (Packet->HoldObjectID >= 0)
			{
				GameServerObject* FindHoldObject = GameServerObject::GetServerObject(Packet->HoldObjectID);
				if (FindHoldObject == nullptr)
				{
					PlayObject->shared_from_this()->CastThis<GamePlayObject>()->SetParentsServerHoldObject(Packet->HoldObjectID);
				}
			}
		}
		else
		{

		}

		return;
	}

	FindObject->PushPacket(_Packet);
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
		else if (ServerObjectType::Object == Packet->Type)
		{
			Packet->ObjectID = GamePlayObject::ObjectNumber_++;
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
		case ContentsPacketType::ObjectStart:
			NewPacket = std::make_shared<ObjectStartPacket>();
			break;
		case ContentsPacketType::ObjectUpdate:
			NewPacket = std::make_shared<ObjectUpdatePacket>();
			break;
		case ContentsPacketType::UIUpdate:
			NewPacket = std::make_shared<UIDataPacket>();
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
	Net->Dis.AddHandler(ContentsPacketType::ObjectUpdate, std::bind(&ServerInitManager::ObjectUpdatePacketProcess, std::placeholders::_1));
	Net->Dis.AddHandler(ContentsPacketType::Ignore, std::bind(&ServerInitManager::Ignore, std::placeholders::_1));
	Net->Dis.AddHandler(ContentsPacketType::None, std::bind(&ServerInitManager::Ignore, std::placeholders::_1));
	Net->Dis.AddHandler(ContentsPacketType::StartLevel, std::bind(&ServerInitManager::StartLevelPacketProcess, std::placeholders::_1));
	Net->Dis.AddHandler(ContentsPacketType::LoadingData, std::bind(&ServerInitManager::LoadingDataPacketProcess, std::placeholders::_1));

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