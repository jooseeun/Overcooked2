#pragma once
#include <GameEngineCore/GameEngineActor.h>
class OverCookedUIRenderer;
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

private:
	OverCookedUIRenderer* EndBackground_ = nullptr;
	OverCookedUIRenderer* Background_ = nullptr;
	OverCookedUIRenderer* Header_ = nullptr;

	GameEngineFontRenderer* CountDownFont_ = nullptr;

	float4 DebugPos_;
	float DebugSize_;
};
