#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "MeshSelectWindow.h"

// Ό³Έν :
class MeshToolLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MeshToolLevel();
	~MeshToolLevel();

	// delete Function
	MeshToolLevel(const MeshToolLevel& _Other) = delete;
	MeshToolLevel(MeshToolLevel&& _Other) noexcept = delete;
	MeshToolLevel& operator=(const MeshToolLevel& _Other) = delete;
	MeshToolLevel& operator=(MeshToolLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	MeshSelectWindow* MeshSelectWindow_;

};

