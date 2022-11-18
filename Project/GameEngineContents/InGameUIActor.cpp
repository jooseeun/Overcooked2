#include "PreCompile.h"
#include "InGameUIActor.h"

#include "OverCookedUIRenderer.h"

#include "GlobalGameData.h"

InGameUIActor::InGameUIActor()
{
}

InGameUIActor::~InGameUIActor()
{
}

void InGameUIActor::UIStart()
{
	TimerUIInst_.Banner = CreateUIRenderer("timer_banner_bg.png");
	TimerUIInst_.Banner->GetTransform().SetLocalPosition({ 420.f,-270.f });

	TimerUIInst_.Bar = CreateUIRenderer("coin_banner_bar_00.png", 0.78f);
	TimerUIInst_.Bar->GetTransform().SetLocalPosition({ 419.f,-286.f });

	TimerUIInst_.HourGlass = CreateUIRenderer("timer_icon.png");
	TimerUIInst_.HourGlass->GetTransform().SetLocalPosition({ 513.f,-270.f });
}

void InGameUIActor::UIUpdate(float _DeltaTime)
{
}