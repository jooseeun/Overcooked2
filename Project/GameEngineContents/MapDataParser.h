#pragma once
#include "Enums.h"
#include <GameEngineCore/GlobalIOManager.h>

class GamePlayStaticObject;
class GamePlayOriginObject;
class GamePlayMapObject;
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

	// ���ĵ��� ���� �� ������ �Ľ�
	std::vector<std::weak_ptr<GamePlayMapObject>>& UnSortMapDataParsing(std::vector<MapData>& _Data, GameEngineLevel* _Level);

	// ���ĵ� �� ������ �Ľ�
	std::vector<std::weak_ptr<GamePlayStaticObject>>& SortMapDataParsing(std::vector<MapData>& _Data, GameEngineLevel* _Level);

	std::vector<std::weak_ptr<GamePlayOriginObject>>& GetOrigins()
	{
		return Origins_;
	}

protected:	

private:
	std::weak_ptr<GamePlayStaticObject> CurActor_;

	std::vector<std::weak_ptr<GamePlayOriginObject>> Origins_;
	std::vector<std::weak_ptr<GamePlayStaticObject>> SortActorList_;
	std::vector<std::weak_ptr<GamePlayMapObject>> UnSortActorList_;

};

	
