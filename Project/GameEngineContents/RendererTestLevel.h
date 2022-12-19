#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class RendererTestLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	RendererTestLevel();
	~RendererTestLevel();

	// delete Function
	RendererTestLevel(const RendererTestLevel& _Other) = delete;
	RendererTestLevel(RendererTestLevel&& _Other) noexcept = delete;
	RendererTestLevel& operator=(const RendererTestLevel& _Other) = delete;
	RendererTestLevel& operator=(RendererTestLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;

private:
	MapDataParser DataParser_;
	bool IsLevelFirst_ = true;

};

