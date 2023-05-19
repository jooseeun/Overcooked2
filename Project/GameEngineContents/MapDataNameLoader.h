#pragma once

// Ό³Έν :
class MapDataNameLoader
{
public:
	// constrcuter destructer
	MapDataNameLoader();
	~MapDataNameLoader();

	// delete Function
	MapDataNameLoader(const MapDataNameLoader& _Other) = delete;
	MapDataNameLoader(MapDataNameLoader&& _Other) noexcept = delete;
	MapDataNameLoader& operator=(const MapDataNameLoader& _Other) = delete;
	MapDataNameLoader& operator=(MapDataNameLoader&& _Other) noexcept = delete;

public:
	void Load(std::vector<std::string>& _Destvector, std::string _FileName);

private:

};

