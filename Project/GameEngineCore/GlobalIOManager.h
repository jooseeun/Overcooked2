#pragma once

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

// Ό³Έν :
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
	static void Save(IOType _Type, int _Value)
	{
		Save(_Type, std::to_string(_Value));
	}
	static void Save(IOType _Type, std::string _AddName = "");

	static void Load(IOType _Type, int _Value)
	{
		Load(_Type, std::to_string(_Value));
	}
	static void Load(IOType _Type, std::string _AddName = "");
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

