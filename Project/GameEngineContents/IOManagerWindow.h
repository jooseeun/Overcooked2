#pragma once
#include <GameEngineCore/GameEngineGUI.h>

struct MapData
{
	MapObjType MapObjType_;
	float4 Pos_;
	float4 Rot_;
	float4 Scale_;
	float4 Tile_;
};

// Ό³Έν :
class IOManagerWindow : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	IOManagerWindow();
	~IOManagerWindow();

	// delete Function
	IOManagerWindow(const IOManagerWindow& _Other) = delete;
	IOManagerWindow(IOManagerWindow&& _Other) noexcept = delete;
	IOManagerWindow& operator=(const IOManagerWindow& _Other) = delete;
	IOManagerWindow& operator=(IOManagerWindow&& _Other) noexcept = delete;

	void AddTileData(MapData _Data);
	void Save(IOType _Type);
	void Load(IOType _Type);

protected:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

private:
	std::vector<MapData> MapDataVector_;

};

