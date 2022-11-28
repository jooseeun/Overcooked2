#pragma once
#include "GamePlayLevel.h"

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
	bool IsLevelFirst_ = true;
};

