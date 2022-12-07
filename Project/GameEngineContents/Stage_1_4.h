#pragma once
#include "GamePlayLevel.h"

struct WallColor
{
	float4 MulColor;
	float4 PlusColor;
	float4 Slice;

	int AlphaFlag;
	float4 AlphaColor;
};

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
	void PlayLevelStart() override;
	void PlayLevelUpdate(float _DeltaTime) override;
	void End() override;
	void PlayLevelStartEvent() override;

private:
	bool IsLevelFirst_ = true;

	WallColor WallColor_;
};
