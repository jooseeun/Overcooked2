#pragma once
#include "UIActor.h"

class TitleLevelActor : public UIActor
{
public:
	TitleLevelActor();
	~TitleLevelActor();

	TitleLevelActor(const TitleLevelActor& _Other) = delete;
	TitleLevelActor(const TitleLevelActor&& _Other) noexcept = delete;
	TitleLevelActor& operator=(const TitleLevelActor& _Ohter) = delete;
	TitleLevelActor& operator=(const TitleLevelActor&& _Other) noexcept = delete;

protected:
	void UIStart() override;
	void UIUpdate(float _DeltaTime) override;
	void UIEnd() override;
};
