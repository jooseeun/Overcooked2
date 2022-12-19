#pragma once
#include "GamePlayLevel.h"
#include "ServerInitManager.h"

class Stage_1_1 : public GamePlayLevel, public ServerInitManager
{
public:
	Stage_1_1();
	~Stage_1_1();

	Stage_1_1(const Stage_1_1& _Other) = delete;
	Stage_1_1(Stage_1_1&& _Other) noexcept = delete;
	Stage_1_1& operator=(const Stage_1_1& _Other) = delete;
	Stage_1_1& operator=(Stage_1_1&& _Other) noexcept = delete;

protected:
	void PlayLevelStart() override;
	void PlayLevelUpdate(float _DeltaTime) override;
	void End() override;

	void PlayLevelStartEvent() override;
private:
	bool IsLevelFirst_ = true;

	std::shared_ptr<GameEngineLight> LightObject_;
};
