#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class UIDebugGUI;
class SelectStageLevel : public GameEngineLevel
{
public:
	SelectStageLevel();
	~SelectStageLevel();

	SelectStageLevel(const SelectStageLevel& _Other) = delete;
	SelectStageLevel(const SelectStageLevel&& _Other) noexcept = delete;
	SelectStageLevel& operator=(const SelectStageLevel& _Ohter) = delete;
	SelectStageLevel& operator=(const SelectStageLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
};
