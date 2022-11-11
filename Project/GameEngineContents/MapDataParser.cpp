#include "PreCompile.h"
#include "MapDataParser.h"
#include "GamePlayOriginObject.h"

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

MapDataParser::MapDataParser()
	: CurAcotr_(nullptr)
{
}

MapDataParser::~MapDataParser()
{
}

void MapDataParser::UnSortMapDataParsing(std::vector<MapData>& _Data, GameEngineLevel* _Level)
{
	for (size_t i = 0; i < _Data.size(); i++)
	{
		if (_Data[i].ObjName_ == "Collision_Floor")
		{
			std::shared_ptr<GamePlayFloor> Object = _Level->CreateActor<GamePlayFloor>();
			Object->GetTransform().SetWorldPosition(_Data[i].Pos_);
			Object->GetTransform().SetWorldRotation(_Data[i].Rot_);
			Object->GetTransform().SetWorldScale(_Data[i].Scale_);
		}
		else if (_Data[i].ObjName_ == "Collision_Wall")
		{
			std::shared_ptr<GamePlayMapObject> Object = _Level->CreateActor<GamePlayMapObject>();
			Object->GetTransform().SetWorldPosition(_Data[i].Pos_);
			Object->GetTransform().SetWorldRotation(_Data[i].Rot_);
			Object->GetTransform().SetWorldScale(_Data[i].Scale_);
		}
		else
		{
			std::shared_ptr<GamePlayMapObject> Object = _Level->CreateActor<GamePlayMapObject>();
			Object->GetTransform().SetWorldPosition(_Data[i].Pos_);
			Object->GetTransform().SetWorldRotation(_Data[i].Rot_);
			Object->GetTransform().SetWorldScale(_Data[i].Scale_);

			std::shared_ptr<GameEngineFBXStaticRenderer> Renderer = Object->CreateComponent<GameEngineFBXStaticRenderer>();
			Renderer->SetFBXMesh(_Data[i].ObjName_ + ".fbx", "Texture");
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
			CurAcotr_ = _Level->CreateActor<CounterTop>();
			std::shared_ptr<CounterTop> Object = std::dynamic_pointer_cast<CounterTop>(CurAcotr_);

			Object->SetCounterTopType(CounterTopType::Normal);
			Object->SetConterTopMesh(CounterTopType::Normal);

			Object->SetStaticObjectType(MapObjType::CounterTop);
		}
		break;
		case MapObjType::CounterTop_Corner:
		{
			CurAcotr_ = _Level->CreateActor<CounterTop>();
			std::shared_ptr<CounterTop> Object = std::dynamic_pointer_cast<CounterTop>(CurAcotr_);

			Object->SetCounterTopType(CounterTopType::Corner);
			Object->SetConterTopMesh(CounterTopType::Corner);

			Object->SetStaticObjectType(MapObjType::CounterTop_Corner);
		}
		break;
		case MapObjType::CounterTop_NoEdge:
		{
			CurAcotr_ = _Level->CreateActor<CounterTop>();
			std::shared_ptr<CounterTop> Object = std::dynamic_pointer_cast<CounterTop>(CurAcotr_);

			Object->SetCounterTopType(CounterTopType::NoEdge);
			Object->SetConterTopMesh(CounterTopType::NoEdge);

			Object->SetStaticObjectType(MapObjType::CounterTop_NoEdge);
		}
		break;
		case MapObjType::CounterTop_WiZard:
			break;
		case MapObjType::Cooker:
		{
			CurAcotr_ = _Level->CreateActor<Cooker>();
			CurAcotr_->SetStaticObjectType(MapObjType::Cooker);
		}
			break;
		case MapObjType::TrashCan:
		{
			CurAcotr_ = _Level->CreateActor<TrashCan>();
			CurAcotr_->SetStaticObjectType(MapObjType::TrashCan);
		}
		break;
		case MapObjType::Sink:
			break;
		case MapObjType::Servicehatch:
		{
			CurAcotr_ = _Level->CreateActor<Servicehatch>();
			CurAcotr_->SetStaticObjectType(MapObjType::Servicehatch);
		}
		break;
		case MapObjType::PlateReturn:
		{
			CurAcotr_ = _Level->CreateActor<PlateReturn>();
			CurAcotr_->SetStaticObjectType(MapObjType::PlateReturn);
		}
		break;
		case MapObjType::FoodBox:
			break;
		default:
			break;
		}
		
		if (nullptr != CurAcotr_)
		{
			ToolInfo ToolType = static_cast<ToolInfo>(_Data[i].Index_.y);

			switch (ToolType)
			{
			case ToolInfo::Plate:
			{
				//부모로 둔다
				std::shared_ptr<Equipment_Plate> Plate = _Level->CreateActor<Equipment_Plate>();
				CurAcotr_->SetStuff(Plate);
			}
			break;
			case ToolInfo::FireExtinguisher:
			{
				std::shared_ptr<Equipment_FireExtinguisher> FireExtinguisher = _Level->CreateActor<Equipment_FireExtinguisher>();
				CurAcotr_->SetStuff(FireExtinguisher);
			}
			break;
			case ToolInfo::FryingPan:
			{
				std::shared_ptr<Equipment_FryingPan> FryingPan = _Level->CreateActor<Equipment_FryingPan>();
				CurAcotr_->SetStuff(FryingPan);
			}
			break;
			case ToolInfo::Pot:
			{
				std::shared_ptr<Equipment_Pot> Pot = _Level->CreateActor<Equipment_Pot>();
				CurAcotr_->SetStuff(Pot);
			}
			break;
			case ToolInfo::CuttingBoard:
			{
				std::shared_ptr<Tool_CuttingBoard> CuttingBoard = _Level->CreateActor<Tool_CuttingBoard>();
				CurAcotr_->SetStuff(CuttingBoard);
			}
			break;
			}

			CurAcotr_->SetParent(Origins_[Order]);
			SortActorList_.push_back(CurAcotr_);

			CurAcotr_->GetTransform().SetWorldPosition(_Data[i].Pos_);
			CurAcotr_->GetTransform().SetWorldRotation(_Data[i].Rot_);
			CurAcotr_->GetTransform().SetWorldScale(_Data[i].Scale_);

			if (nullptr != CurAcotr_->GetStuff())
			{
				float4 ToolPos = CurAcotr_->GetToolPos();
				CurAcotr_->GetStuff()->GetTransform().SetWorldPosition(ToolPos);
			}

			Origins_[Order]->GetStaticMeshInfo().push_back(CurAcotr_);

			CurAcotr_ = nullptr;
		}
	}

	return SortActorList_;
}

