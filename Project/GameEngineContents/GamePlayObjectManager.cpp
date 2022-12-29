#include "PreCompile.h"
#include <GameEngineCore/GEngine.h>
#include "GamePlayObjectManager.h"
#include "Player.h"

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

std::mutex ObjectManagerLock;

GamePlayObjectManager* GamePlayObjectManager::Inst_ = nullptr;
std::queue<std::shared_ptr<GameServerPacket>> GamePlayObjectManager::TemporaryPacket;

GamePlayObjectManager::GamePlayObjectManager() 
{
}

GamePlayObjectManager::~GamePlayObjectManager() 
{
}

void GamePlayObjectManager::Start()
{

}

void GamePlayObjectManager::TemporaryPushData(std::shared_ptr<ObjectStartPacket> _Update)
{
	//std::lock_guard L(ObjectManagerLock);
	TemporaryPacket.push(_Update);
}

void GamePlayObjectManager::Update(float _Time)
{
	while (!TemporaryPacket.empty())
	{
		std::lock_guard L(ObjectManagerLock);
		switch (TemporaryPacket.front()->GetPacketIDToEnum<ContentsPacketType>())
		{
		case ContentsPacketType::ObjectStart:
			QueueMapData_.push(std::dynamic_pointer_cast<ObjectStartPacket>(TemporaryPacket.front()));
			break;
		case ContentsPacketType::ObjectParentsSet:
			QueueObjectParentsSet_.push(std::dynamic_pointer_cast<ObjectParentsSetPacket>(TemporaryPacket.front()));
			break;
		case ContentsPacketType::ObjectInteractUpdate:
			break;
		case ContentsPacketType::ObjectUpdate:

			break;
		default:
			MsgBoxAssert("GamePlayObjectManager - 처리할수없는 패킷이 들어 왔습니다")
			break;
		}

		TemporaryPacket.pop();
	}
	

	while (!QueueMapData_.empty())
	{
		PopMapDataData();
	}
	while (!QueueObjectParentsSet_.empty())
	{
		PopMapDataData();
	}
}

bool GamePlayObjectManager::Isempty()
{
	std::lock_guard L(ObjectManagerLock);
	return QueueMapData_.empty();
}


void GamePlayObjectManager::PushMapData(std::shared_ptr<ObjectStartPacket> _Update)
{
	std::lock_guard L(ObjectManagerLock);
	QueueMapData_.push(_Update);
}

void GamePlayObjectManager::PushParentsSetData(std::shared_ptr<ObjectParentsSetPacket> _Packet)
{
	std::lock_guard L(ObjectManagerLock);
	QueueObjectParentsSet_.push(_Packet);
}

void GamePlayObjectManager::PopObjectParentsSetData()
{
	if (QueueObjectParentsSet_.empty())
	{
		return;
	}

	std::shared_ptr<GamePlayObject> PlayObject;
	std::shared_ptr<ObjectParentsSetPacket> Packet;
	{
		std::lock_guard L(ObjectManagerLock);
		Packet = QueueObjectParentsSet_.front();
		QueueObjectParentsSet_.pop();
	}

	GameServerObject* FindHoldObject = GameServerObject::GetServerObject(Packet->ChildID);
	if (FindHoldObject != nullptr)
	{
		return;
	}

	FindHoldObject = GameServerObject::GetServerObject(Packet->ParentsID);
	if (FindHoldObject == nullptr)
	{
		MsgBoxAssert("GamePlayObjectManager::PopObjectParentsSetData() - FindHoldObject 부모가 nullptr입니다")
	}

	switch (FindHoldObject->GetServerType())
	{
	case ServerObjectType::Player:
	{
		std::shared_ptr<Player> Player_ = ((Player*)(FindHoldObject))->shared_from_this()->CastThis<Player>();
		std::shared_ptr<GamePlayMoveable> Moveable = Player_->GetPlayerHolding()->CastThis<GamePlayMoveable>();		// Nullptr이면 무조건 잘못 된것

		if (Moveable->GetIsNetInit() == false)
		{
			Moveable->ClientInit(ServerObjectType::Object, Packet->ChildID);
		}
	}
		break;
	case ServerObjectType::Object:
	{
		std::shared_ptr<GamePlayObject> Object = ((GamePlayObject*)(FindHoldObject))->shared_from_this()->CastThis<GamePlayObject>();
		Object->SetParentsServerHoldObject(Packet->ChildID);
		//std::shared_ptr<GamePlayMoveable> Moveable = Player_->GetPlayerHolding()->CastThis<GamePlayMoveable>();		// Nullptr이면 무조건 잘못 된것

		//if (Moveable->GetIsNetInit() == false)
		//{
		//	Moveable->ClientInit(ServerObjectType::Object, Packet->ChildID);
		//}
	}
		break;
	case ServerObjectType::UI:
		MsgBoxAssert("GamePlayObjectManager::PopObjectParentsSetData() - 잘못된 형식")
		break;
	default:
		MsgBoxAssert("GamePlayObjectManager::PopObjectParentsSetData() - 서버에 등록되지 않았습니다")
		break;
	}



	
}

std::shared_ptr<GamePlayObject> GamePlayObjectManager::PopMapDataData()
{
	if (QueueMapData_.empty())
	{
		return nullptr;
	}

	std::shared_ptr<GamePlayObject> PlayObject;
	std::shared_ptr<ObjectStartPacket> Packet;
	{
		std::lock_guard L(ObjectManagerLock);
		Packet = QueueMapData_.front();
		QueueMapData_.pop();
	}

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
			Object.lock()->SetFoodType(static_cast<IngredientType>(Packet->IngredientData));
		}
		break;
		case MapObjType::FoodBox_Winter:
		{
			CurActor_ = GEngine::GetCurrentLevel()->CreateActor<FoodBox>();
			CurActor_.lock()->SetStaticObjectType(MapObjType::FoodBox_Winter);

			std::weak_ptr<FoodBox> Object = std::dynamic_pointer_cast<FoodBox>(CurActor_.lock());
			Object.lock()->SetFoodBoxMesh(FoodBoxType::Winter);
			Object.lock()->SetFoodType(static_cast<IngredientType>(Packet->IngredientData));
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
		PlayObject = GamePlayFood::GetIngredientClass(Packet->IngredientData);
	}
	else
	{
		MsgBoxAssert("ServerInitManager 처리할수 없는 Object 데이터")
	}
	PlayObject->ClientInit(ServerObjectType::Object, Packet->ObjectID);

	PlayObject->GetTransform().SetWorldPosition(Packet->Pos);
	PlayObject->GetTransform().SetWorldRotation(Packet->Rot);
	PlayObject->GetTransform().SetWorldScale(Packet->Scale);

	//GamePlayObject::ObjectNumber_ = Packet->ObjectID + 1;

	if (Packet->HoldObjectID >= 0)
	{
		GameServerObject* FindHoldObject = GameServerObject::GetServerObject(Packet->HoldObjectID);
		if (FindHoldObject == nullptr)
		{
			//	MsgBoxAssert("ServerinitManager - HoldingObject가 서버에 등록되어 있지 않습니다");
			PlayObject->shared_from_this()->CastThis<GamePlayObject>()->SetParentsServerHoldObject(Packet->HoldObjectID);
		}
		else
		{
			PlayObject->shared_from_this()->CastThis<GamePlayObject>()->SetServerHoldObject(Packet->HoldObjectID);
		}
	}


	return PlayObject;
}

GamePlayObjectManager* GamePlayObjectManager::GetInst()
{
	return Inst_;
}

void GamePlayObjectManager::LevelStartEvent()
{
	GamePlayObjectManager::Inst_ = this;
}

void GamePlayObjectManager::LevelEndEvent()
{
	GamePlayObjectManager::Inst_ = nullptr;

	QueueObjectParentsSet_ = std::queue<std::shared_ptr<ObjectParentsSetPacket>>();
	QueueMapData_ = std::queue<std::shared_ptr<ObjectStartPacket>>();

	TemporaryPacket = std::queue<std::shared_ptr<GameServerPacket>>(); // 초기화
}