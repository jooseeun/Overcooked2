#pragma once
#include "GamePlayLevel.h"

class Stage_1_4 : public GamePlayLevel
{
public:
	Stage_1_4();
	~Stage_1_4();

	Stage_1_4(const Stage_1_4& _Other) = delete;
	Stage_1_4(Stage_1_4&& _Other) noexcept = delete;
	Stage_1_4& operator=(const Stage_1_4& _Other) = delete;
	Stage_1_4& operator=(Stage_1_4&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

