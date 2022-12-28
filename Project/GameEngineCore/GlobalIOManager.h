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
	CounterTop_Winter,
	Mixer_Kevin,
	Mixer_Winter,
	Cooker,			//가스레인지
	TrashCan,			//쓰레기통
	Sink,				//싱크대
	Sink_Wizard,		//마법사 싱크대
	Servicehatch,		//요리 내는 창구
	PlateReturn,		//그릇 되돌아 나오는 타일
	FoodBox_Normal,		//음식 스폰 박스
	FoodBox_Winter,
	Rail,				//컨베이어 벨트
	Dispenser_Type1,
	Dispenser_Type2,
	Cannon,
	Button,
	Oven,

	Pigeon_Grounded,		// 애니메이션 O, 콜리전 x		ex) Pigeon_Idle
	Animation,				// 애니메이션 O				ex) Kevin
	Npc,					// 애니메이션 O, 콜리전 O
	Car,					// 애니메이션 X
	TrafficLight,			// 애니메이션 X
	Candle,					// 애니메이션 X
	Lift,					// 애니메이션 X, 콜리전 O
	Portal_Blue,
	Portal_Purple,
	Collision_Wall,			// 벽, 바닥용 콜리전
	Collision_Floor,
	Robin_Grounded,
	IceBlock,
	IcePlatform,
	Collision_DeadZone,
	Beam,

	Max,
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