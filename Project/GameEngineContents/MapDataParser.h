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

	// ���ĵ��� ���� �� ������ �Ľ�
	void UnSortMapDataParsing(std::vector<MapData>& _Data, GameEngineLevel* _Level);

	// ���ĵ� �� ������ �Ľ�
	std::vector<GamePlayStaticObject*>& SortMapDataParsing(std::vector<MapData>& _Data, GameEngineLevel* _Level);

	std::vector<GamePlayOriginObject*>& GetOrigins()
	{
		return Origins_;
	}

protected:	

private:
	class GamePlayStaticObject* CurAcotr_;

	std::vector<GamePlayOriginObject*> Origins_;
};

	
