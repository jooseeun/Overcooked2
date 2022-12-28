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
	CounterTop_WiZard,  //������ �������� ���� ������
	CounterTop_Winter,
	Mixer_Kevin,
	Mixer_Winter,
	Cooker,			//����������
	TrashCan,			//��������
	Sink,				//��ũ��
	Sink_Wizard,		//������ ��ũ��
	Servicehatch,		//�丮 ���� â��
	PlateReturn,		//�׸� �ǵ��� ������ Ÿ��
	FoodBox_Normal,		//���� ���� �ڽ�
	FoodBox_Winter,
	Rail,				//�����̾� ��Ʈ
	Dispenser_Type1,
	Dispenser_Type2,
	Cannon,
	Button,
	Oven,

	Pigeon_Grounded,		// �ִϸ��̼� O, �ݸ��� x		ex) Pigeon_Idle
	Animation,				// �ִϸ��̼� O				ex) Kevin
	Npc,					// �ִϸ��̼� O, �ݸ��� O
	Car,					// �ִϸ��̼� X
	TrafficLight,			// �ִϸ��̼� X
	Candle,					// �ִϸ��̼� X
	Lift,					// �ִϸ��̼� X, �ݸ��� O
	Portal_Blue,
	Portal_Purple,
	Collision_Wall,			// ��, �ٴڿ� �ݸ���
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

// ���� :
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