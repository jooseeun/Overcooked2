#include "PreCompile.h"
#include "MapDataParser.h"
#include "GamePlayOriginObject.h"

#include "CounterTop.h"

MapDataParser::MapDataParser()
{
}

MapDataParser::~MapDataParser()
{
}

void MapDataParser::UnSortMapDataParsing(std::vector<MapData>& _Data, GameEngineLevel* _Level)
{
}

void MapDataParser::SortMapDataParsing(std::vector<MapData>& _Data, GameEngineLevel* _Level)
{
	for (size_t i = 0; i < _Data.size(); ++i)
	{
		//기준 엑터라면
		if (MapObjType::Origin == _Data[i].MapObjType_)
		{
			GamePlayOriginObject* Origin = _Level->CreateActor<GamePlayOriginObject>();

			Origins_.push_back(Origin);
		}
	}

	for (size_t i = 0; i < _Data.size(); i++)
	{
		switch (_Data[i].MapObjType_)
		{
			int Order = _Data[i].Index_.z;

		case MapObjType::CounterTop:
		{
			CurAcotr_ = _Level->CreateActor<CounterTop>();
			CurAcotr_->SetParent(Origins_[Order]);
		}
		break;
		case MapObjType::CounterTop_Corner:
			break;
		case MapObjType::CounterTop_NoEdge:
			break;
		case MapObjType::CounterTop_WiZard:
			break;
		case MapObjType::GasRange:
			break;
		case MapObjType::TrashCan:
			break;
		case MapObjType::Sink:
			break;
		case MapObjType::Servicehatch:
			break;
		case MapObjType::FoodBox:
			break;
		default:
			break;
		}

		CurAcotr_->GetTransform().SetWorldPosition(_Data[i].Pos_);
		CurAcotr_->GetTransform().SetWorldPosition(_Data[i].Rot_);
		CurAcotr_->GetTransform().SetWorldPosition(_Data[i].Scale_);
	}
}

