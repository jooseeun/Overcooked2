#pragma once
#include "GamePlayLevel.h"

class Stage_1_1 : public GamePlayLevel
{
public:
	Stage_1_1();
	~Stage_1_1();

	Stage_1_1(const Stage_1_1& _Other) = delete;
	Stage_1_1(Stage_1_1&& _Other) noexcept = delete;
	Stage_1_1& operator=(const Stage_1_1& _Other) = delete;
	Stage_1_1& operator=(Stage_1_1&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

