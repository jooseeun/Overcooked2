#pragma once
#include "UIActor.h"
class InGameUIActor : public UIActor
{
public:
	InGameUIActor();
	~InGameUIActor();

	InGameUIActor(const InGameUIActor& _Other) = delete;
	InGameUIActor(const InGameUIActor&& _Other) noexcept = delete;
	InGameUIActor& operator=(const InGameUIActor& _Ohter) = delete;
	InGameUIActor& operator=(const InGameUIActor&& _Other) noexcept = delete;

protected:
	void UIStart() override;
	void UIUpdate(float _DeltaTime) override;

private:
	struct TimerUI
	{
		std::shared_ptr<OverCookedUIRenderer> Banner;
		std::shared_ptr<OverCookedUIRenderer> Bar;
		std::shared_ptr<OverCookedUIRenderer> HourGlass;
		std::shared_ptr<GameEngineFontRenderer> Time;
	};

	TimerUI TimerUIInst_;
};
