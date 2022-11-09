#include "PreCompile.h"
#include "MapDataParser.h"
#include "GamePlayOriginObject.h"

#include "CounterTop.h"
#include "TrashCan.h"
#include "Servicehatch.h"

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
			GamePlayFloor* Object = _Level->CreateActor<GamePlayFloor>();
			Object->GetTransform().SetWorldPosition(_Data[i].Pos_);
			Object->GetTransform().SetWorldRotation(_Data[i].Rot_);
			Object->GetTransform().SetWorldScale(_Data[i].Scale_);
		}
		else if (_Data[i].ObjName_ == "Collision_Wall")
		{
			GamePlayMapObject* Object = _Level->CreateActor<GamePlayMapObject>();
			Object->GetTransform().SetWorldPosition(_Data[i].Pos_);
			Object->GetTransform().SetWorldRotation(_Data[i].Rot_);
			Object->GetTransform().SetWorldScale(_Data[i].Scale_); 
		}
		else
		{
			GamePlayMapObject* Object = _Level->CreateActor<GamePlayMapObject>();
			Object->GetTransform().SetWorldPosition(_Data[i].Pos_);
			Object->GetTransform().SetWorldRotation(_Data[i].Rot_);
			Object->GetTransform().SetWorldScale(_Data[i].Scale_);

			GameEngineFBXStaticRenderer* Renderer = Object->CreateComponent<GameEngineFBXStaticRenderer>();
			Renderer->SetFBXMesh(_Data[i].ObjName_ + ".fbx", "Texture");
		}
	}
}

std::vector<GamePlayStaticObject*>& MapDataParser::SortMapDataParsing(std::vector<MapData>& _Data, GameEngineLevel* _Level)
{
	SortActorList_.clear();

	for (size_t i = 0; i < _Data.size(); ++i)
	{
		//기준 엑터라면
		if (MapObjType::Origin == _Data[i].MapObjType_)
		{
			GamePlayOriginObject* Origin = _Level->CreateActor<GamePlayOriginObject>();

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
			CounterTop* Object = dynamic_cast<CounterTop*>(CurAcotr_);

			Object->SetCounterTopType(CounterTopType::Normal);
			Object->SetConterTopMesh(CounterTopType::Normal);
		}
		break;
		case MapObjType::CounterTop_Corner:
		{
			CurAcotr_ = _Level->CreateActor<CounterTop>();
			CounterTop* Object = dynamic_cast<CounterTop*>(CurAcotr_);

			Object->SetCounterTopType(CounterTopType::Corner);
			Object->SetConterTopMesh(CounterTopType::Corner);

			Object->SetStaticObjectType(MapObjType::CounterTop_Corner);
		}
			break;
		case MapObjType::CounterTop_NoEdge:
		{
			CurAcotr_ = _Level->CreateActor<CounterTop>();
			CounterTop* Object = dynamic_cast<CounterTop*>(CurAcotr_);

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
		case MapObjType::FoodBox:
			break;
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

			CurAcotr_ = nullptr;
		}
	}	

	return SortActorList_;
}

