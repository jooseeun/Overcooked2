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

struct MeshData
{
	std::string MeshName_;
	std::string Path_;
	std::string MaterialName_;
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

	static void AddMeshData(MeshData _Data);
	static void AddMapData(MapData _Data);
	static void Save(IOType _Type);
	static void Load(IOType _Type);
	static void Clear();

	static std::vector<MapData>& GetMapDataVector()
	{
		return MapDataVector_;
	}
	static std::vector<MeshData>& GetMeshDataVector()
	{
		return MeshDataVector_;
	}

protected:

private:
	static std::vector<MapData> MapDataVector_;
	static std::vector<MeshData> MeshDataVector_;

};

