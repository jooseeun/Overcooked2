#pragma once
#include "GamePlayLevel.h"

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
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

