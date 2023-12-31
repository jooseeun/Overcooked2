#pragma once
#include "GamePlayLevel.h"

class Player;
class Cannon;
class Stage_2_1 : public GamePlayLevel
{
public:
	// constrcuter destructer
	Stage_2_1();
	~Stage_2_1();

	// delete Function
	Stage_2_1(const Stage_2_1& _Other) = delete;
	Stage_2_1(Stage_2_1&& _Other) noexcept = delete;
	Stage_2_1& operator=(const Stage_2_1& _Other) = delete;
	Stage_2_1& operator=(Stage_2_1&& _Other) noexcept = delete;

protected:
	void PlayLevelStart() override;
	void PlayLevelUpdate(float _DeltaTime) override;
	void End() override;
	void PlayLevelStartEvent() override;

private:
	std::shared_ptr<GameEngineLight> LightObject_;


	RenderOption WaterRenderOption1_;
	RenderOption WaterRenderOption2_;

	std::shared_ptr<GameEngineActor> WaterActor_;
	std::shared_ptr<Cannon> CannonObj_;
	bool IsLevelFirst_ = true;
};

