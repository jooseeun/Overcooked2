#pragma once

enum class IOType
{
	Mesh,
	UnsortMap,
	SortMap,
	Max,
};

enum class MapObjType
{
	Origin,
	CounterTop,
	CounterTop_Corner,
	CounterTop_NoEdge,
	CounterTop_WiZard,  //마법사 스테이지 전용 조리대
	GasRange,			//가스레인지
	TrashCan,			//쓰레기통
	Sink,				//싱크대
	Servicehatch,		//요리 내는 창구
	FoodBox,			//음식 스폰 박스
	Npc_Static,			// 움직이지 않는 NPC
	Npc_Move,			// 1-2 레벨 내 움직이는 NPC
	Car_Static,			// 움직이지 않는 자동차
	Car_Move,			// 1-2 레벨 내 움직이는 자동차
	Grass,
	Pigeon,
	TrafficLight,
	Candle_Move,		// 1-4 레벨 내 움직이는 초
	Collision,			// 벽, 바닥용 콜리전
};

struct MapData
{
	std::string ObjName_;
	MapObjType MapObjType_;
	GameEngineTransform* Transform_;
	float4 Pos_;
	float4 Rot_;
	float4 Scale_;
	float4 Index_;
};

struct SubSetMeshData
{
	std::string DifTexturePath_;
	std::string DifTextureName_;
};

struct MeshData
{
	std::string PreviewMeshName_;
	std::vector<SubSetMeshData> PreviewMeshInfo_;
};

// 설명 :
class GlobalIOManager
{
public:
	// constrcuter destructer
	GlobalIOManager();
	~GlobalIOManager();

	// delete Function
	GlobalIOManager(const GlobalIOManager& _Other) = delete;
	GlobalIOManager(GlobalIOManager&& _Other) noexcept = delete;
	GlobalIOManager& operator=(const GlobalIOManager& _Other) = delete;
	GlobalIOManager& operator=(GlobalIOManager&& _Other) noexcept = delete;

	static void SetMeshData(MeshData _Data);
	static void AddMapData(MapData _Data);
	static bool Save(IOType _Type, int _Value)
	{
		return Save(_Type, std::to_string(_Value));
	}
	static bool Save(IOType _Type, std::string _AddName = "");

	static bool Load(IOType _Type, int _Value)
	{
		return Load(_Type, std::to_string(_Value));
	}
	static bool Load(IOType _Type, std::string _AddName = "");
	static void Clear();

	static std::vector<MapData>& GetMapDataVector()
	{
		return MapDataVector_;
	}
	static MeshData& GetMeshData()
	{
		return MeshData_;
	}

protected:

private:
	static std::vector<MapData> MapDataVector_;
	static MeshData MeshData_;

};

