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

#include "Lift.h"
#include "Portal.h"
#include "MoveCar.h"
#include "IcePlatform.h"

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

void GamePlayObjectManager::TemporaryPushData(std::shared_ptr<GameServerPacket> _Update)
{
	std::lock_guard L(ObjectManagerLock);
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
			QueueObjectInteraction_.push(std::dynamic_pointer_cast<ObjectInteractUpdatePacket>(TemporaryPacket.front()));
			break;
		case ContentsPacketType::ObjectParentsSetFrame:
			QueueObjectParentsSetAllFrame_.push(std::dynamic_pointer_cast<ObjectParentsSetAllFramePacket>(TemporaryPacket.front()));
			break;
		case ContentsPacketType::ObjectCookingGageUpdate:
			QueueObjectCookingGage_.push(std::dynamic_pointer_cast<ObjectCookingGagePacket>(TemporaryPacket.front()));
			break;
		case ContentsPacketType::ObjectUpdate:
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
	while (!QueueObjectCookingGage_.empty())
	{
		PopObjectCookingData();
	}
	while (!QueueObjectInteraction_.empty())
	{
		PopObjectInteractData();
	}
	while (!QueueObjectParentsSet_.empty())
	{
		PopObjectParentsSetData();
	}
	while (!QueueObjectParentsSetAllFrame_.empty())
	{
		PopObjectParentsSetAllFrameData();
	}
}

void GamePlayObjectManager::PopObjectCookingData()
{
	if (QueueObjectCookingGage_.empty())
	{
		return;
	}

	std::shared_ptr<GamePlayObject> PlayObject;
	std::shared_ptr<ObjectCookingGagePacket> Packet;
	{
		std::lock_guard L(ObjectManagerLock);
		Packet = QueueObjectCookingGage_.front();
		QueueObjectCookingGage_.pop();
	}

	GameServerObject* FindParentsObject = GameServerObject::GetServerObject(Packet->ObjectID);

	if (FindParentsObject == nullptr)
	{
		TemporaryPushData(Packet);
	}

	PlayObject = ((GamePlayObject*)(FindParentsObject))->shared_from_this()->CastThis<GamePlayObject>();
	PlayObject->SetServerCookingGage(Packet);
}

bool GamePlayObjectManager::Isempty()
{
	std::lock_guard L(ObjectManagerLock);
	return QueueMapData_.empty();
}

void GamePlayObjectManager::PushObjectInteractData(std::shared_ptr<ObjectInteractUpdatePacket> _Update)
{
	std::lock_guard L(ObjectManagerLock);
	QueueObjectInteraction_.push(_Update);
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

	GameServerObject* FindParentsObject = GameServerObject::GetServerObject(Packet->ParentsID);

	if (Packet->ChildID > 0 && GameServerObject::GetServerObject(Packet->ChildID) == nullptr)
	{
		TemporaryPushData(Packet);
		return;
	}

	switch (FindParentsObject->GetServerType())
	{
	case ServerObjectType::Player:
	{
		std::shared_ptr<Player> Player_ = ((Player*)(FindParentsObject))->shared_from_this()->CastThis<Player>();
		if (Packet->ChildID == -1)
		{
			Player_->CurrentHoldingNull();
			return;
		}
		else
		{
			std::shared_ptr<GamePlayObject> Child = ((GamePlayObject*)(GameServerObject::GetServerObject(Packet->ChildID)))->shared_from_this()->CastThis<GamePlayObject>();
			
			if (Child == nullptr)
			{
				MsgBoxAssert("GamePlayObjectManager::PopObjectParentsSetData() / Child is Nullptr")
				return;
			}
			else
			{
				Player_->SetPlayerHolding(Child);
			}
		}
	}
	break;
	case ServerObjectType::Object:
	{
		std::shared_ptr<GamePlayObject> Object = ((GamePlayObject*)(FindParentsObject))->shared_from_this()->CastThis<GamePlayObject>();
		std::shared_ptr<GamePlayStuff> Child = ((GamePlayStuff*)(GameServerObject::GetServerObject(Packet->ChildID)))->shared_from_this()->CastThis<GamePlayStuff>();


		if (Object->CastThis<GamePlayStaticObject>() != nullptr)
		{
			if (Packet->ChildID == -1)
			{
				Object->CastThis<GamePlayStaticObject>()->ReSetStuff();
			}
			else
			{
				Child->CastThis<GamePlayStaticObject>()->SetStuff(Child);
			}
		}
		else
		{
			if (Packet->ChildID == -1)
			{
				Object->CastThis<GamePlayTool>()->ReSetCurrentMoveable();
			}
			else
			{
				Object->CastThis<GamePlayTool>()->SetMoveable(Child);
			}
		}
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
		case MapObjType::IcePlatform:
		{
			std::weak_ptr<IcePlatform> Object = GEngine::GetCurrentLevel()->CreateActor<IcePlatform>();
			//Object.lock()->GetCollisionObject()->GetTransform().SetWorldScale(Packet->Scale);
			Object.lock()->SetMapObjType(MapObjType::IcePlatform);

			PlayObject = Object.lock();
		}
		break;
		case MapObjType::Lift:
		{
			std::weak_ptr<Lift> Object = GEngine::GetCurrentLevel()->CreateActor<Lift>();
			Object.lock()->SetMapObjectMesh("m_city_liftplatform_01", MapObjType::Lift);
			//Object.lock()->GetCollisionObject()->GetTransform().SetWorldScale(Packet->Scale);
			Object.lock()->SetMapObjType(MapObjType::Lift);
			PlayObject = Object.lock();
		}
		break;
		case MapObjType::Portal_Blue:
		case MapObjType::Portal_Purple:
		{
			std::weak_ptr<Portal> Object = GEngine::GetCurrentLevel()->CreateActor<Portal>();
			Object.lock()->GetCollisionObject()->GetTransform().SetWorldScale(Packet->Scale);
			Object.lock()->SetMapObjType(Packet->MapObjData);
			Object.lock()->SetPortalMesh(Packet->MapObjData);
			PlayObject = Object.lock();
		}
		break;
		default:
			break;
		}
		if (PlayObject == nullptr)
		{
			PlayObject = CurActor_.lock();
		}
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

		PlayObject->ClientInit(ServerObjectType::Object, Packet->ObjectID);
		Tool_FoodBox::map_FoodQueue_[Packet->IngredientData].push(PlayObject->CastThis<GamePlayFood>());

		return PlayObject;
		//if (!Tool_FoodBox::map_FoodDeque_[Packet->IngredientData].empty())
		//{
		//	Tool_FoodBox::Deque_ServerInit(Packet->IngredientData, Packet->ObjectID);
		//	return PlayObject;
		//}
		//

	}
	else if(Packet->ObjectToolData != ObjectToolType::None)
	{
		GameServerObject* FindHoldObject = GameServerObject::GetServerObject(Packet->ObjectID);
		if (FindHoldObject == nullptr)
		{
			TemporaryPushData(Packet);
			return nullptr;
		}
		else
		{
			PlayObject = ((GamePlayObject*)(FindHoldObject))->shared_from_this()->CastThis<GamePlayObject>();
		}
		//return nullptr;
	}
	else if (Packet->ExceptionData != ExceptionObject::None)
	{
	switch (Packet->ExceptionData)
	{
		case ExceptionObject::MoveCar:
		{
			std::shared_ptr<MoveCar> Car = GEngine::GetCurrentLevel()->CreateActor<MoveCar>();
			Car->SetCarMesh(Packet->Animation);
			PlayObject = Car;
		}
			break;
		default:
			MsgBoxAssert("ServerInitManager 아직 설정되지 않은 예외오브젝트를 생성하려고 하였습니다")
			break;
		}
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

void GamePlayObjectManager::PopObjectInteractData()
{
	if (QueueObjectInteraction_.empty())
	{
		return;
	}

	std::shared_ptr<ObjectInteractUpdatePacket> Packet;
	{
		std::lock_guard L(ObjectManagerLock);
		Packet = QueueObjectInteraction_.front();
		QueueObjectInteraction_.pop();
	}
	
	GameServerObject* FindObject = GameServerObject::GetServerObject(Packet->PlayerNum);
	if (FindObject == nullptr)
	{
		TemporaryPushData(Packet);
		GameEngineDebug::OutPutString("Cant Find " + std::to_string(Packet->PlayerNum));
		return;
	}
	else
	{
		FindObject = GameServerObject::GetServerObject(Packet->ObjectID);
		FindObject->PushPacket(Packet);
	}

}

void GamePlayObjectManager::PopObjectParentsSetAllFrameData()
{
	if (QueueObjectParentsSetAllFrame_.empty())
	{
		return;
	}

	std::shared_ptr<ObjectParentsSetAllFramePacket> Packet;
	{
		std::lock_guard L(ObjectManagerLock);
		Packet = QueueObjectParentsSetAllFrame_.front();
		QueueObjectParentsSetAllFrame_.pop();
	}

	GameServerObject* FindParentObject = GameServerObject::GetServerObject(Packet->ParentsID);
	if (FindParentObject == nullptr)
	{
		TemporaryPushData(Packet);
		GameEngineDebug::OutPutString("Cant Find " + std::to_string(Packet->ParentsID));
		return;
	}

	GameServerObject* FindChildObject = GameServerObject::GetServerObject(Packet->ChildID);

	if (FindChildObject == nullptr)
	{
		TemporaryPushData(Packet);
		GameEngineDebug::OutPutString("Cant Find " + std::to_string(Packet->ParentsID));
		return;
	}

	FindParentObject->PushPacket(Packet);


	//if (ServerInitManager::Net->GetIsHost())
	//{
	//	std::shared_ptr<ObjectParentsSetAllFramePacket> ParentsSetPacket = std::make_shared<ObjectParentsSetAllFramePacket>();
	//	ParentsSetPacket->ParentsID = GetNetID();
	//	if (CurrentHoldingObject_ == nullptr)
	//	{
	//		ParentsSetPacket->ChildID = -1;
	//	}
	//	else
	//	{
	//		ParentsSetPacket->ChildID = CurrentHoldingObject_->CastThis<GamePlayObject>()->GetNetID();
	//	}
	//	ServerInitManager::Net->SendPacket(ParentsSetPacket);
	//}

	//		case ContentsPacketType::ObjectParentsSetFrame:
	//		{
	//			std::shared_ptr<ObjectParentsSetAllFramePacket> ParentsSetPacket = std::dynamic_pointer_cast<ObjectParentsSetAllFramePacket>(Packet);
	//			if (ParentsSetPacket->ChildID == -1)
	//			{
	//				CurrentHoldingNull();
	//			}
	//			else
	//			{
	//				GameServerObject* FindObject = GameServerObject::GetServerObject(ParentsSetPacket->ChildID);
	//				SetPlayerHolding(((GamePlayObject*)(FindObject))->shared_from_this());
	//			}
	//		}
	//		break;

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

	//QueueObjectParentsSet_ = std::queue<std::shared_ptr<ObjectParentsSetPacket>>();
	QueueMapData_ = std::queue<std::shared_ptr<ObjectStartPacket>>();

	TemporaryPacket = std::queue<std::shared_ptr<GameServerPacket>>(); // 초기화
	QueueObjectInteraction_ = std::queue<std::shared_ptr<ObjectInteractUpdatePacket>>(); // 초기화
	//QueueObjectParentsSet_ = std::queue<std::shared_ptr<ObjectParentsSetPacket>>(); // 초기화
	QueueObjectParentsSetAllFrame_ = std::queue<std::shared_ptr<ObjectParentsSetAllFramePacket>>(); // 초기화
	QueueObjectCookingGage_ = std::queue<std::shared_ptr<ObjectCookingGagePacket>>();

}