#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class MapEditor : public GameEngineActor
{
public:
	static MapEditor* MainMapEditor_;

	// constrcuter destructer
	MapEditor();
	~MapEditor();

	// delete Function
	MapEditor(const MapEditor& _Other) = delete;
	MapEditor(MapEditor&& _Other) noexcept = delete;
	MapEditor& operator=(const MapEditor& _Other) = delete;
	MapEditor& operator=(MapEditor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

