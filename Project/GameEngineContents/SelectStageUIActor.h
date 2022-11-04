#pragma once
#include <GameEngineCore/GameEngineActor.h>
class SelectStageUIActor : public GameEngineActor
{
public:
	SelectStageUIActor();
	~SelectStageUIActor();

	SelectStageUIActor(const SelectStageUIActor& _Other) = delete;
	SelectStageUIActor(const SelectStageUIActor&& _Other) noexcept = delete;
	SelectStageUIActor& operator=(const SelectStageUIActor& _Ohter) = delete;
	SelectStageUIActor& operator=(const SelectStageUIActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
};
