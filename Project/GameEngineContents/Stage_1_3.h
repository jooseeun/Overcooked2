#pragma once
#include "GamePlayLevel.h"

class Stage_1_3 : public GamePlayLevel
{
public:
	Stage_1_3();
	~Stage_1_3();

	Stage_1_3(const Stage_1_3& _Other) = delete;
	Stage_1_3(Stage_1_3&& _Other) noexcept = delete;
	Stage_1_3& operator=(const Stage_1_3& _Other) = delete;
	Stage_1_3& operator=(Stage_1_3&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	void PlayLevelStartEvent() override;

private:
	bool IsLevelFirst_ = true;
};
