#include "PreCompile.h"
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

#include "Equipment_Plate.h"
#include "Equipment_FireExtinguisher.h"
#include "Equipment_FryingPan.h"
#include "Equipment_Pot.h"
#include "Tool_CuttingBoard.h"

#include "Npc.h"
#include "Car.h"
#include "TrafficLight.h"
#include "Candle.h"

MapDataParser::MapDataParser()
	: CurActor_()
{
}

MapDataParser::~MapDataParser()
{
}

std::vector<std::weak_ptr<GamePlayMapObject>>& MapDataParser::UnSortMapDataParsing(std::vector<MapData>& _Data, GameEngineLevel* _Level)
{
	UnSortActorList_.clear();

	for (size_t i = 0; i < _Data.size(); i++)
	{
		switch (_Data[i].MapObjType_)
		{
		case MapObjType::Npc:
		{
			std::weak_ptr<Npc> Object = _Level->CreateActor<Npc>();
			Object.lock()->GetTransform().SetWorldPosition(_Data[i].Pos_);
			Object.lock()->GetCollisionObject()->GetTransform().SetWorldScale(_Data[i].Scale_);
			Object.lock()->GetTransform().SetWorldRotation(_Data[i].Rot_);
			Object.lock()->SetMapObjectMesh(_Data[i].ObjName_, _Data[i].MapObjType_);
			Object.lock()->SetMapObjType(_Data[i].MapObjType_);
			Object.lock()->SetName(_Data[i].ObjName_);
			UnSortActorList_.push_back(Object);
		}
		break;
		case MapObjType::Car:
		{
			std::weak_ptr<Car> Object = _Level->CreateActor<Car>();
			Object.lock()->GetTransform().SetWorldPosition(_Data[i].Pos_);
			Object.lock()->GetCollisionObject()->GetTransform().SetWorldScale(_Data[i].Scale_);
			Object.lock()->GetTransform().SetWorldRotation(_Data[i].Rot_);
			Object.lock()->SetMapObjectMesh(_Data[i].ObjName_, _Data[i].MapObjType_);
			Object.lock()->SetMapObjType(_Data[i].MapObjType_);
			Object.lock()->SetName(_Data[i].ObjName_);
			UnSortActorList_.push_back(Object);
		}
		break;
		case MapObjType::TrafficLight:
		{
			std::weak_ptr<TrafficLight> Object = _Level->CreateActor<TrafficLight>();
			Object.lock()->GetTransform().SetWorldPosition(_Data[i].Pos_);
			Object.lock()->GetCollisionObject()->GetTransform().SetWorldScale(_Data[i].Scale_);
			Object.lock()->GetTransform().SetWorldRotation(_Data[i].Rot_);
			Object.lock()->SetMapObjectMesh(_Data[i].ObjName_, _Data[i].MapObjType_);
			Object.lock()->SetMapObjType(_Data[i].MapObjType_);
			Object.lock()->SetName(_Data[i].ObjName_);
			UnSortActorList_.push_back(Object);
		}
		break;
		case MapObjType::Candle:
		{
			std::weak_ptr<Candle> Object = _Level->CreateActor<Candle>();
			Object.lock()->GetTransform().SetWorldPosition(_Data[i].Pos_);
			Object.lock()->GetCollisionObject()->GetTransform().SetWorldScale(_Data[i].Scale_);
			Object.lock()->GetTransform().SetWorldRotation(_Data[i].Rot_);
			Object.lock()->SetMapObjectMesh(_Data[i].ObjName_, _Data[i].MapObjType_);
			Object.lock()->SetMapObjType(_Data[i].MapObjType_);
			Object.lock()->SetName(_Data[i].ObjName_);
			Object.lock()->SetCandleTypeIndex((int)_Data[i].Index_.x);
			
			UnSortActorList_.push_back(Object);
		}
		break;
		case MapObjType::Pigeon_Grounded:
		{
			std::weak_ptr<GamePlayMapObject> Object = _Level->CreateActor<GamePlayMapObject>();
			Object.lock()->GetTransform().SetWorldPosition(_Data[i].Pos_);
			Object.lock()->GetAnimationFBXMesh()->GetTransform().SetLocalScale({ 150.f, 150.f, 150.f });
			Object.lock()->GetCollisionObject()->GetTransform().SetWorldScale(_Data[i].Scale_);
			Object.lock()->GetTransform().SetWorldRotation(_Data[i].Rot_);
			Object.lock()->SetMapObjectMesh(_Data[i].ObjName_, _Data[i].MapObjType_);
			Object.lock()->SetMapObjType(_Data[i].MapObjType_);
			Object.lock()->SetName(_Data[i].ObjName_);
			UnSortActorList_.push_back(Object);
		}
		break;
		case MapObjType::Collision_Wall:
		{
			std::weak_ptr<GamePlayMapObject> Object = _Level->CreateActor<GamePlayMapObject>();
			Object.lock()->GetTransform().SetWorldPosition(_Data[i].Pos_);
			Object.lock()->GetCollisionObject()->GetTransform().SetWorldScale(_Data[i].Scale_);
			Object.lock()->GetTransform().SetWorldRotation(_Data[i].Rot_);
			Object.lock()->SetMapObjectMesh(_Data[i].ObjName_, _Data[i].MapObjType_);
			Object.lock()->SetMapObjType(_Data[i].MapObjType_);
			Object.lock()->SetName(_Data[i].ObjName_);
			UnSortActorList_.push_back(Object);
		}
		break;
		case MapObjType::Collision_Floor:
		{
			std::weak_ptr<GamePlayFloor> Object = _Level->CreateActor<GamePlayFloor>();
			Object.lock()->GetTransform().SetWorldPosition(_Data[i].Pos_);
			Object.lock()->GetCollisionObject()->GetTransform().SetWorldScale(_Data[i].Scale_);
			Object.lock()->GetTransform().SetWorldRotation(_Data[i].Rot_);
			Object.lock()->SetMapObjectMesh(_Data[i].ObjName_, _Data[i].MapObjType_);
			Object.lock()->SetMapObjType(_Data[i].MapObjType_);
			Object.lock()->SetName(_Data[i].ObjName_);
			UnSortActorList_.push_back(Object);
		}
		break;
		default:
		{
			std::weak_ptr<GamePlayMapObject> Object = _Level->CreateActor<GamePlayMapObject>();
			Object.lock()->GetTransform().SetWorldPosition(_Data[i].Pos_);
			Object.lock()->GetCollisionObject()->GetTransform().SetWorldScale(_Data[i].Scale_);
			Object.lock()->GetTransform().SetWorldRotation(_Data[i].Rot_);
			Object.lock()->SetMapObjectMesh(_Data[i].ObjName_, _Data[i].MapObjType_);
			Object.lock()->SetMapObjType(_Data[i].MapObjType_);
			Object.lock()->SetName(_Data[i].ObjName_);
			if (_Data[i].ObjName_ == "m_kevin_01")
			{
				Object.lock()->GetAnimationFBXMesh()->GetTransform().SetLocalScale({65.f, 65.f, 65.f});
			}
			UnSortActorList_.push_back(Object);
		}
		break;
		}
	}

	return UnSortActorList_;
}

std::vector<std::weak_ptr<GamePlayStaticObject>>& MapDataParser::SortMapDataParsing(std::vector<MapData>& _Data, GameEngineLevel* _Level)
{
	SortActorList_.clear();

	for (size_t i = 0; i < _Data.size(); ++i)
	{
		//기준 엑터라면
		if (MapObjType::Origin == _Data[i].MapObjType_)
		{
			std::weak_ptr<GamePlayOriginObject> Origin = _Level->CreateActor<GamePlayOriginObject>();

			Origin.lock()->GetTransform().SetWorldPosition(_Data[i].Pos_);
			Origin.lock()->GetTransform().SetWorldRotation(_Data[i].Rot_);
			Origin.lock()->GetTransform().SetWorldScale(_Data[i].Scale_);

			Origins_.push_back(Origin); 
		}
	}

	for (size_t i = 0; i < _Data.size(); i++)
	{
		int Order = _Data[i].Index_.z;

		switch (_Data[i].MapObjType_)
		{
		case MapObjType::CounterTop:
		{
			CurActor_ = _Level->CreateActor<CounterTop>();
			std::weak_ptr<CounterTop> Object = std::dynamic_pointer_cast<CounterTop>(CurActor_.lock());

			Object.lock()->SetCounterTopType(CounterTopType::Normal);
			Object.lock()->SetConterTopMesh(CounterTopType::Normal);

			Object.lock()->SetStaticObjectType(MapObjType::CounterTop);
		}
		break;
		case MapObjType::CounterTop_Corner:
		{
			CurActor_= _Level->CreateActor<CounterTop>();
			std::weak_ptr<CounterTop> Object = std::dynamic_pointer_cast<CounterTop>(CurActor_.lock());

			Object.lock()->SetCounterTopType(CounterTopType::Corner);
			Object.lock()->SetConterTopMesh(CounterTopType::Corner);

			Object.lock()->SetStaticObjectType(MapObjType::CounterTop_Corner);
		}
		break;
		case MapObjType::CounterTop_NoEdge:
		{
			CurActor_ = _Level->CreateActor<CounterTop>();
			std::weak_ptr<CounterTop> Object = std::dynamic_pointer_cast<CounterTop>(CurActor_.lock());

			Object.lock()->SetCounterTopType(CounterTopType::NoEdge);
			Object.lock()->SetConterTopMesh(CounterTopType::NoEdge);

			Object.lock()->SetStaticObjectType(MapObjType::CounterTop_NoEdge);
		}
		break;
		case MapObjType::CounterTop_WiZard:
		{
			CurActor_ = _Level->CreateActor<CounterTop>();
			std::weak_ptr<CounterTop> Object = std::dynamic_pointer_cast<CounterTop>(CurActor_.lock());

			Object.lock()->SetCounterTopType(CounterTopType::Wizard);
			Object.lock()->SetConterTopMesh(CounterTopType::Wizard);

			Object.lock()->SetStaticObjectType(MapObjType::CounterTop_WiZard);
		}
			break;
		case MapObjType::Cooker:
		{
			CurActor_ = _Level->CreateActor<Cooker>();
			CurActor_.lock()->SetStaticObjectType(MapObjType::Cooker);
		}	
			break;
		case MapObjType::TrashCan:
		{
			CurActor_ = _Level->CreateActor<TrashCan>();
			CurActor_.lock()->SetStaticObjectType(MapObjType::TrashCan);
		}
		break;
		case MapObjType::Sink:
		{
			CurActor_ = _Level->CreateActor<Sink>();
			CurActor_.lock()->SetStaticObjectType(MapObjType::Sink);
			std::weak_ptr<Sink> Object = std::dynamic_pointer_cast<Sink>(CurActor_.lock());
			Object.lock()->SetSinkMesh(SinkType::Normal);
		}
			break;
		case MapObjType::Servicehatch:
		{
			CurActor_ = _Level->CreateActor<Servicehatch>();
			CurActor_.lock()->SetStaticObjectType(MapObjType::Servicehatch);
		}
		break;
		case MapObjType::PlateReturn:
		{
			CurActor_ = _Level->CreateActor<PlateReturn>();
			CurActor_.lock()->SetStaticObjectType(MapObjType::PlateReturn);
		}
		break;
		case MapObjType::FoodBox:
			CurActor_ = _Level->CreateActor<FoodBox>();
			CurActor_.lock()->SetStaticObjectType(MapObjType::FoodBox);
			break;
		case MapObjType::Sink_Wizard: 
		{
			CurActor_ = _Level->CreateActor<Sink>();
			CurActor_.lock()->SetStaticObjectType(MapObjType::Sink_Wizard);

			std::weak_ptr<Sink> Object = std::dynamic_pointer_cast<Sink>(CurActor_.lock());
			Object.lock()->SetSinkMesh(SinkType::Wizard);
		}
			break;
		case MapObjType::Rail:
		{
			CurActor_ = _Level->CreateActor<Rail>();
			CurActor_.lock()->SetStaticObjectType(MapObjType::Rail);
		}
		break;
		default:
			break;
		}
		
		if (nullptr != CurActor_.lock())
		{
			ToolInfo ToolType = static_cast<ToolInfo>(_Data[i].Index_.y);

			switch (ToolType)
			{
			case ToolInfo::Plate:
			{
				//부모로 둔다
				std::weak_ptr<Equipment_Plate> Plate = _Level->CreateActor<Equipment_Plate>();
				CurActor_.lock()->SetStuff(Plate.lock());
			}
			break;
			case ToolInfo::FireExtinguisher:
			{
				std::weak_ptr<Equipment_FireExtinguisher> FireExtinguisher = _Level->CreateActor<Equipment_FireExtinguisher>();
				CurActor_.lock()->SetStuff(FireExtinguisher.lock());
			}
			break;
			case ToolInfo::FryingPan:
			{
				std::weak_ptr<Equipment_FryingPan> FryingPan = _Level->CreateActor<Equipment_FryingPan>();
				CurActor_.lock()->SetStuff(FryingPan.lock());
			}
			break;
			case ToolInfo::Pot:
			{
				std::weak_ptr<Equipment_Pot> Pot = _Level->CreateActor<Equipment_Pot>();
				CurActor_.lock()->SetStuff(Pot.lock());
			}
			break;
			case ToolInfo::CuttingBoard:
			{
				std::weak_ptr<Tool_CuttingBoard> CuttingBoard = _Level->CreateActor<Tool_CuttingBoard>();
				CurActor_.lock()->SetStuff(CuttingBoard.lock());
			}
			break;
			}

			CurActor_.lock()->SetParent(Origins_[Order].lock());
			SortActorList_.push_back(CurActor_);

			CurActor_.lock()->GetTransform().SetWorldPosition(_Data[i].Pos_);
			CurActor_.lock()->GetTransform().SetWorldRotation(_Data[i].Rot_);
			CurActor_.lock()->GetTransform().SetWorldScale(_Data[i].Scale_);

			if (nullptr != CurActor_.lock()->GetStuff())
			{
				float4 ToolPos = CurActor_.lock()->GetToolPos();
				CurActor_.lock()->GetStuff()->GetTransform().SetWorldPosition(ToolPos);
			}

			Origins_[Order].lock()->GetStaticMeshInfo().push_back(CurActor_.lock());
			CurActor_.reset();
		}
	}

	return SortActorList_;
}

