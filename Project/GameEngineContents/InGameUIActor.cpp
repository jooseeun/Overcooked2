#include "PreCompile.h"
#include "InGameUIActor.h"

#include "OverCookedUIRenderer.h"

#include "GlobalGameData.h"

using namespace ContentsUtility;

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

	TimerUIInst_.Time = CreateComponent<GameEngineFontRenderer>();
	TimerUIInst_.Time->ChangeCamera(CAMERAORDER::UICAMERA);
	TimerUIInst_.Time->SetText("03:06", "Naughty Squirrel");
	TimerUIInst_.Time->SetColor({ 1.0f,1.0f,1.0f,1 });
	TimerUIInst_.Time->SetSize(30.f);
	TimerUIInst_.Time->SetLeftAndRightSort(LeftAndRightSort::LEFT);
	TimerUIInst_.Time->SetAffectTransform(true);

	//ÆùÆ®
	ResistDebug("TimeFont", TimerUIInst_.Time->GetTransform());
	TimerUIInst_.Time->GetTransform().SetLocalMove({ 370,-236.f,-1 });
}

void InGameUIActor::UIUpdate(float _DeltaTime)
{
	//UpdateTime
	ContentsUtility::Timer& LeftTimer = GlobalGameData::GetLeftTimeRef();
	LeftTimer.Update(_DeltaTime);
	TimerUIInst_.Time->SetText(std::to_string(LeftTimer.GetCurTime()), "Naughty Squirrel");

	int Minute = static_cast<int>(LeftTimer.GetCurTime() / 60.f);
	int Seconds = static_cast<int>(LeftTimer.GetCurTime()) % 60;

	if (Minute >= 10) // 11 :
	{
		if (Seconds >= 10) // 11 : 24
		{
			TimerUIInst_.Time->SetText(std::to_string(Minute) + ":" + std::to_string(Seconds), "Naughty Squirrel");
		}
		else // 11 : 02
		{
			TimerUIInst_.Time->SetText(std::to_string(Minute) + ":0" + std::to_string(Seconds), "Naughty Squirrel");
		}
	}
	else // 01 :
	{
		if (Seconds >= 10) // 01 : 11
		{
			TimerUIInst_.Time->SetText("0" + std::to_string(Minute) + ":" + std::to_string(Seconds), "Naughty Squirrel");
		}
		else // 01 : 01
		{
			TimerUIInst_.Time->SetText("0" + std::to_string(Minute) + ":0" + std::to_string(Seconds), "Naughty Squirrel");
		}
	}
}