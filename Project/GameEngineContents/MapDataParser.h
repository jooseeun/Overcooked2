#pragma once
#include "Enums.h"
#include <GameEngineCore/GlobalIOManager.h>

class GamePlayStaticObject;
class GamePlayOriginObject;
class GameEngineLevel;
class MapDataParser
{
public:
	MapDataParser();
	~MapDataParser();

	MapDataParser(const MapDataParser& _Other) = delete;
	MapDataParser(MapDataParser&& _Other) noexcept = delete;
	MapDataParser& operator=(const MapDataParser& _Other) = delete;
	MapDataParser& operator=(MapDataParser&& _Other) noexcept = delete;

	// 정렬되지 않은 맵 데이터 파싱
	void UnSortMapDataParsing(std::vector<MapData>& _Data, GameEngineLevel* _Level);

	// 정렬된 맵 데이터 파싱
	std::vector<std::shared_ptr<GamePlayStaticObject>>& SortMapDataParsing(std::vector<MapData>& _Data, GameEngineLevel* _Level);

	std::vector<std::shared_ptr<GamePlayOriginObject>>& GetOrigins()
	{
		return Origins_;
	}

protected:	

private:
	std::shared_ptr<GamePlayStaticObject> CurActor_;

	std::vector<std::shared_ptr<GamePlayOriginObject>> Origins_;
	std::vector<std::shared_ptr<GamePlayStaticObject>> SortActorList_;
};

	
