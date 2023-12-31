#pragma once
#include "GamePlayLevel.h"

class DownCar;
class Stage_1_2 : public GamePlayLevel
{
public:
	Stage_1_2();
	~Stage_1_2();

	Stage_1_2(const Stage_1_2& _Other) = delete;
	Stage_1_2(Stage_1_2&& _Other) noexcept = delete;
	Stage_1_2& operator=(const Stage_1_2& _Other) = delete;
	Stage_1_2& operator=(Stage_1_2&& _Other) noexcept = delete;

protected:
	void PlayLevelStart() override;
	void PlayLevelUpdate(float _DeltaTime) override;
	void End() override;
	void PlayLevelStartEvent() override;

private:
	bool IsLevelFirst_ = true;
};
