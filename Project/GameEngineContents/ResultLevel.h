#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class ResultLevel : public GameEngineLevel
{
public:
	ResultLevel();
	~ResultLevel();

	ResultLevel(const ResultLevel& _Other) = delete;
	ResultLevel(const ResultLevel&& _Other) noexcept = delete;
	ResultLevel& operator=(const ResultLevel& _Ohter) = delete;
	ResultLevel& operator=(const ResultLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	void LevelStartEvent() override;
	void LevelEndEvent() override;
};
