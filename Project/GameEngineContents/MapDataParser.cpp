#include "PreCompile.h"
#include "MapDataParser.h"
#include "GamePlayOriginObject.h"
#include "GamePlayMapObject.h"

#include "CounterTop.h"
#include "TrashCan.h"
#include "Servicehatch.h"
#include "PlateReturn.h"
#include "Cooker.h"

#include "Equipment_Plate.h"
#include "Equipment_FireExtinguisher.h"
#include "Equipment_FryingPan.h"
#include "Equipment_Pot.h"
#include "Tool_CuttingBoard.h"

#include "Npc.h"
#include "Car.h"
#include "TrafficLight.h"

MapDataParser::MapDataParser()
	: CurActor_(nullptr)
{
}

MapDataParser::~MapDataParser()
{
}

void MapDataParser::UnSortMapDataParsing(std::vector<MapData>& _Data, GameEngineLevel* _Level)
{
	for (size_t i = 0; i < _Data.size(); i++)
	{
		switch (_Data[i].MapObjType_)
		{
		case MapObjType::Npc:
		{
			std::shared_ptr<Npc> Object = _Level->CreateActor<Npc>();
			Object->GetTransform().SetWorldPosition(_Data[i].Pos_);
			Object->GetCollisionObject()->GetTransform().SetWorldScale(_Data[i].Scale_);
			Object->GetTransform().SetWorldRotation(_Data[i].Rot_);
			Object->SetMapObjectMesh(_Data[i].ObjName_, _Data[i].MapObjType_);
			Object->SetMapObjType(_Data[i].MapObjType_);
			Object->SetName(_Data[i].ObjName_);
		}
		break;
		case MapObjType::Car:
		{
			std::shared_ptr<Car> Object = _Level->CreateActor<Car>();
			Object->GetTransform().SetWorldPosition(_Data[i].Pos_);
			Object->GetCollisionObject()->GetTransform().SetWorldScale(_Data[i].Scale_);
			Object->GetTransform().SetWorldRotation(_Data[i].Rot_);
			Object->SetMapObjectMesh(_Data[i].ObjName_, _Data[i].MapObjType_);
			Object->SetMapObjType(_Data[i].MapObjType_);
			Object->SetName(_Data[i].ObjName_);
		}
		break;
		case MapObjType::TrafficLight:
		{
			std::shared_ptr<TrafficLight> Object = _Level->CreateActor<TrafficLight>();
			Object->GetTransform().SetWorldPosition(_Data[i].Pos_);
			Object->GetCollisionObject()->GetTransform().SetWorldScale(_Data[i].Scale_);
			Object->GetTransform().SetWorldRotation(_Data[i].Rot_);
			Object->SetMapObjectMesh(_Data[i].ObjName_, _Data[i].MapObjType_);
			Object->SetMapObjType(_Data[i].MapObjType_);
			Object->SetName(_Data[i].ObjName_);
		}
		break;
		case MapObjType::Collision_Wall:
		{
			std::shared_ptr<GamePlayMapObject> Object = _Level->CreateActor<GamePlayMapObject>();
			Object->GetTransform().SetWorldPosition(_Data[i].Pos_);
			Object->GetCollisionObject()->GetTransform().SetWorldScale(_Data[i].Scale_);
			Object->GetTransform().SetWorldRotation(_Data[i].Rot_);
			Object->SetMapObjectMesh(_Data[i].ObjName_, _Data[i].MapObjType_);
			Object->SetMapObjType(_Data[i].MapObjType_);
			Object->SetName(_Data[i].ObjName_);
		}
		break;
		case MapObjType::Collision_Floor:
		{
			std::shared_ptr<GamePlayFloor> Object = _Level->CreateActor<GamePlayFloor>();
			Object->GetTransform().SetWorldPosition(_Data[i].Pos_);
			Object->GetCollisionObject()->GetTransform().SetWorldScale(_Data[i].Scale_);
			Object->GetTransform().SetWorldRotation(_Data[i].Rot_);
			Object->SetMapObjectMesh(_Data[i].ObjName_, _Data[i].MapObjType_);
			Object->SetMapObjType(_Data[i].MapObjType_);
			Object->SetName(_Data[i].ObjName_);

		}
		break;
		default:
		{
			std::shared_ptr<GamePlayMapObject> Object = _Level->CreateActor<GamePlayMapObject>();
			Object->GetTransform().SetWorldPosition(_Data[i].Pos_);
			Object->GetCollisionObject()->GetTransform().SetWorldScale(_Data[i].Scale_);
			Object->GetTransform().SetWorldRotation(_Data[i].Rot_);
			Object->SetMapObjectMesh(_Data[i].ObjName_, _Data[i].MapObjType_);
			Object->SetMapObjType(_Data[i].MapObjType_);
			Object->SetName(_Data[i].ObjName_);
		}
		break;
		}
	}
}

std::vector<std::shared_ptr<GamePlayStaticObject>>& MapDataParser::SortMapDataParsing(std::vector<MapData>& _Data, GameEngineLevel* _Level)
{
	SortActorList_.clear();

	for (size_t i = 0; i < _Data.size(); ++i)
	{
		//기준 엑터라면
		if (MapObjType::Origin == _Data[i].MapObjType_)
		{
			std::shared_ptr<GamePlayOriginObject> Origin = _Level->CreateActor<GamePlayOriginObject>();

			Origin->GetTransform().SetWorldPosition(_Data[i].Pos_);
			Origin->GetTransform().SetWorldRotation(_Data[i].Rot_);
			Origin->GetTransform().SetWorldScale(_Data[i].Scale_);

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
			std::shared_ptr<CounterTop> Object = std::dynamic_pointer_cast<CounterTop>(CurActor_);

			Object->SetCounterTopType(CounterTopType::Normal);
			Object->SetConterTopMesh(CounterTopType::Normal);

			Object->SetStaticObjectType(MapObjType::CounterTop);
		}
		break;
		case MapObjType::CounterTop_Corner:
		{
			CurActor_ = _Level->CreateActor<CounterTop>();
			std::shared_ptr<CounterTop> Object = std::dynamic_pointer_cast<CounterTop>(CurActor_);

			Object->SetCounterTopType(CounterTopType::Corner);
			Object->SetConterTopMesh(CounterTopType::Corner);

			Object->SetStaticObjectType(MapObjType::CounterTop_Corner);
		}
		break;
		case MapObjType::CounterTop_NoEdge:
		{
			CurActor_ = _Level->CreateActor<CounterTop>();
			std::shared_ptr<CounterTop> Object = std::dynamic_pointer_cast<CounterTop>(CurActor_);

			Object->SetCounterTopType(CounterTopType::NoEdge);
			Object->SetConterTopMesh(CounterTopType::NoEdge);

			Object->SetStaticObjectType(MapObjType::CounterTop_NoEdge);
		}
		break;
		case MapObjType::CounterTop_WiZard:
			break;
		case MapObjType::Cooker:
		{
			CurActor_ = _Level->CreateActor<Cooker>();
			CurActor_->SetStaticObjectType(MapObjType::Cooker);
		}	
			break;
		case MapObjType::TrashCan:
		{
			CurActor_ = _Level->CreateActor<TrashCan>();
			CurActor_->SetStaticObjectType(MapObjType::TrashCan);
		}
		break;
		case MapObjType::Sink:
			break;
		case MapObjType::Servicehatch:
		{
			CurActor_ = _Level->CreateActor<Servicehatch>();
			CurActor_->SetStaticObjectType(MapObjType::Servicehatch);
		}
		break;
		case MapObjType::PlateReturn:
		{
			CurActor_ = _Level->CreateActor<PlateReturn>();
			CurActor_->SetStaticObjectType(MapObjType::PlateReturn);
		}
		break;
		case MapObjType::FoodBox:
			break;
		default:
			break;
		}
		
		if (nullptr != CurActor_)
		{
			ToolInfo ToolType = static_cast<ToolInfo>(_Data[i].Index_.y);

			switch (ToolType)
			{
			case ToolInfo::Plate:
			{
				//부모로 둔다
				std::shared_ptr<Equipment_Plate> Plate = _Level->CreateActor<Equipment_Plate>();
				CurActor_->SetStuff(Plate);
			}
			break;
			case ToolInfo::FireExtinguisher:
			{
				std::shared_ptr<Equipment_FireExtinguisher> FireExtinguisher = _Level->CreateActor<Equipment_FireExtinguisher>();
				CurActor_->SetStuff(FireExtinguisher);
			}
			break;
			case ToolInfo::FryingPan:
			{
				std::shared_ptr<Equipment_FryingPan> FryingPan = _Level->CreateActor<Equipment_FryingPan>();
				CurActor_->SetStuff(FryingPan);
			}
			break;
			case ToolInfo::Pot:
			{
				std::shared_ptr<Equipment_Pot> Pot = _Level->CreateActor<Equipment_Pot>();
				CurActor_->SetStuff(Pot);
			}
			break;
			case ToolInfo::CuttingBoard:
			{
				std::shared_ptr<Tool_CuttingBoard> CuttingBoard = _Level->CreateActor<Tool_CuttingBoard>();
				CurActor_->SetStuff(CuttingBoard);
			}
			break;
			}

			CurActor_->SetParent(Origins_[Order]);
			SortActorList_.push_back(CurActor_);

			CurActor_->GetTransform().SetWorldPosition(_Data[i].Pos_);
			CurActor_->GetTransform().SetWorldRotation(_Data[i].Rot_);
			CurActor_->GetTransform().SetWorldScale(_Data[i].Scale_);

			if (nullptr != CurActor_->GetStuff())
			{
				float4 ToolPos = CurActor_->GetToolPos();
				CurActor_->GetStuff()->GetTransform().SetWorldPosition(ToolPos);
			}

			Origins_[Order]->GetStaticMeshInfo().push_back(CurActor_);

			CurActor_ = nullptr;
		}
	}

	return SortActorList_;
}

