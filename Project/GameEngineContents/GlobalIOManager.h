#pragma once

struct MapData
{
	MapObjType MapObjType_;
	GameEngineActor* Actor_;
	float4 Tile_;
};

// Ό³Έν :
class GlobalIOManager
{
private:
	static GlobalIOManager* Inst_;

public:
	static GlobalIOManager* GetInst()
	{
		return Inst_;
	}

public:
	// constrcuter destructer
	GlobalIOManager();
	~GlobalIOManager();

	// delete Function
	GlobalIOManager(const GlobalIOManager& _Other) = delete;
	GlobalIOManager(GlobalIOManager&& _Other) noexcept = delete;
	GlobalIOManager& operator=(const GlobalIOManager& _Other) = delete;
	GlobalIOManager& operator=(GlobalIOManager&& _Other) noexcept = delete;

	static void AddTileData(MapData _Data);
	static void Save(IOType _Type);
	static void Load(IOType _Type);
	static void Clear();

protected:

private:
	static std::vector<MapData> MapDataVector_;

};

