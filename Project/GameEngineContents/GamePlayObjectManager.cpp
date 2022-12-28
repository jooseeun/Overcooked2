#include "PreCompile.h"
#include <GameEngineCore/GEngine.h>
#include "GamePlayObjectManager.h"

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

GamePlayObjectManager::GamePlayObjectManager() 
{
}

GamePlayObjectManager::~GamePlayObjectManager() 
{
}

void GamePlayObjectManager::Start()
{

}

void GamePlayObjectManager::Update(float _Time)
{
	while (!QueueMapData_.empty())
	{
		PopData();
	}
}

bool GamePlayObjectManager::Isempty()
{
	std::lock_guard L(ObjectManagerLock);
	return QueueMapData_.empty();
}

void GamePlayObjectManager::PushData(std::shared_ptr<ObjectStartPacket> _Update)
{
	std::lock_guard L(ObjectManagerLock);
	MapData Data;

	Data.MapObjType_ = _Update->MapObjData;
	Data.Pos_ = _Update->Pos;
	Data.Rot_ = _Update->Rot;
	Data.Scale_ = _Update->Scale;
	Data.Index_.x = static_cast<float>(_Update->ToolData);
	Data.Index_.y = static_cast<float>(_Update->IngredientData);
	Data.Index_.z = static_cast<float>(_Update->HoldObjectID);

	QueueMapData_.push(std::pair<int, MapData>(_Update->ObjectID, Data));
}

std::shared_ptr<GamePlayObject> GamePlayObjectManager::PopData()
{
	if (QueueMapData_.empty())
	{
		return nullptr;
	}

	std::lock_guard L(ObjectManagerLock);
	int NetID = QueueMapData_.front().first;
	MapData Data = QueueMapData_.front().second;

	std::shared_ptr<GamePlayObject> PlayObject;

	if (Data.MapObjType_ != MapObjType::Max)
	{
		std::weak_ptr<GamePlayStaticObject> CurActor_;
		switch (Data.MapObjType_)
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
			Object.lock()->SetFoodType(static_cast<IngredientType>(Data.Index_.y));
		}
		break;
		case MapObjType::FoodBox_Winter:
		{
			CurActor_ = GEngine::GetCurrentLevel()->CreateActor<FoodBox>();
			CurActor_.lock()->SetStaticObjectType(MapObjType::FoodBox_Winter);

			std::weak_ptr<FoodBox> Object = std::dynamic_pointer_cast<FoodBox>(CurActor_.lock());
			Object.lock()->SetFoodBoxMesh(FoodBoxType::Winter);
			Object.lock()->SetFoodType(static_cast<IngredientType>(Data.Index_.y));
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
	else if (static_cast<ToolInfo>(Data.Index_.x) != ToolInfo::None)
	{
		switch (static_cast<ToolInfo>(Data.Index_.x))
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
	else if (static_cast<IngredientType>(Data.Index_.y) != IngredientType::None)
	{
		PlayObject = GamePlayFood::GetIngredientClass(static_cast<IngredientType>(Data.Index_.y));
	}
	else
	{
		MsgBoxAssert("ServerInitManager 처리할수 없는 Object 데이터")
	}
	PlayObject->ClientInit(ServerObjectType::Object, NetID);

	PlayObject->GetTransform().SetWorldPosition(Data.Pos_);
	PlayObject->GetTransform().SetWorldRotation(Data.Rot_);
	PlayObject->GetTransform().SetWorldScale(Data.Scale_);

	GamePlayObject::ObjectNumber_ = ++NetID;

	int HoldObjectID = static_cast<int>(Data.Index_.z);
	if (HoldObjectID >= 0)
	{
		GameServerObject* FindHoldObject = GameServerObject::GetServerObject(HoldObjectID);
		if (FindHoldObject == nullptr)
		{
			//	MsgBoxAssert("ServerinitManager - HoldingObject가 서버에 등록되어 있지 않습니다");
			PlayObject->shared_from_this()->CastThis<GamePlayObject>()->SetParentsServerHoldObject(HoldObjectID);
		}
		else
		{
			PlayObject->shared_from_this()->CastThis<GamePlayObject>()->SetServerHoldObject(HoldObjectID);
		}
	}
	QueueMapData_.pop();

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
}