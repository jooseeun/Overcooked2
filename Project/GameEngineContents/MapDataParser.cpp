#include "PreCompile.h"
#include "MapDataParser.h"
#include "GamePlayOriginObject.h"

#include "CounterTop.h"
#include "TrashCan.h"
#include "Servicehatch.h"
#include "PlateReturn.h"

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

		ToolInfo ToolType = static_cast<ToolInfo>(_Data[i].Index_.w);

		switch (ToolType)
		{
		default:
			break;
		}


		if (nullptr != CurAcotr_)
		{
			CurAcotr_->SetParent(Origins_[Order]);
			SortActorList_.push_back(CurAcotr_);

			CurAcotr_->GetTransform().SetWorldPosition(_Data[i].Pos_);
			CurAcotr_->GetTransform().SetWorldRotation(_Data[i].Rot_);
			CurAcotr_->GetTransform().SetWorldScale(_Data[i].Scale_);

			Origins_[Order]->GetStaticMeshInfo().push_back(CurAcotr_);

			CurAcotr_ = nullptr;
		}
	}

	return SortActorList_;
}

