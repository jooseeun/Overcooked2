#pragma once
#include "Enums.h"
#include "GlobalIOManager.h"

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
	void SortMapDataParsing(std::vector<MapData>& _Data, GameEngineLevel* _Level);

protected:	

private:
	class GamePlayStaticObject* CurAcotr_;

	std::vector<class GamePlayOriginObject*> Origins_;
};


