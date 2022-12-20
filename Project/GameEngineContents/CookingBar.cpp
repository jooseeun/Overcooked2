#include "PreCompile.h"
#include "CookingBar.h"
#include "FoodThumbnail.h"

#include "GlobalGameData.h"
#include "UIDebugGUI.h"

#include <GameEngineCore/GameEngineCameraActor.h>

CookingBar::CookingBar()
{
}

CookingBar::~CookingBar()
{
}

void CookingBar::LinkObject(std::shared_ptr<GameEngineActor> _Actor, const float4& _Offset, float* _LinkValue, bool _IsOver)
{
	ChaseActor_ = _Actor;
	Offset_ = _Offset;
	UpdateValue_ = _LinkValue;
	IsOver_ = _IsOver;
}

void CookingBar::Start()
{
	Background_ = CreateComponent<OverCookedUIRenderer>();
	Background_.lock()->SetTexture("CookingBackground.png");
	Background_.lock()->ScaleToTexture();
	Background_.lock()->ChangeCamera(CAMERAORDER::USER7);
	Background_.lock()->Off();

	Foreground_ = CreateComponent<OverCookedUIRenderer>();
	Foreground_.lock()->SetTexture("CookingForeground.png");
	Foreground_.lock()->ScaleToTexture();
	Foreground_.lock()->ChangeCamera(CAMERAORDER::USER7);
	Foreground_.lock()->Off();

	Icon_ = CreateComponent<OverCookedUIRenderer>();
	Icon_.lock()->SetTexture("CookingTick.png");
	Icon_.lock()->SetScaleRatio(0.19f);
	Icon_.lock()->ScaleToTexture();
	Icon_.lock()->ChangeCamera(CAMERAORDER::USER7);
	Icon_.lock()->Off();
}

void CookingBar::Update(float _DeltaTime)
{
	if (ChaseActor_.lock() == nullptr)
	{
		return;
	}
	if (ChaseActor_.lock()->IsDeath() == true)
	{
		Death();
		return;
	}
	ChaseTarget();
	//Update Bar
	UpdateBar(_DeltaTime);
}

void CookingBar::UpdateBar(float _DeltaTime)
{
	float Value = *UpdateValue_ / 100.0f;

	if (Value <= 0.001f)
	{
		Foreground_.lock()->Off();
		Background_.lock()->Off();
	}
	else if (Value >= 1.0f)
	{
		Foreground_.lock()->Off();
		Background_.lock()->Off();

		if (IsOver_ == true && Value < 1.5f)
		{
			Icon_.lock()->On();
			IterTime_ += _DeltaTime * 1.4f;
			float4 Color;
			if (IterTime_ < 1.f)
			{
				Color = { 1.f,1.f,1.f,IterTime_ };
			}
			else if (IterTime_ >= 1.f && IterTime_ < 2.f)
			{
				Color = { 1.f,1.f,1.f,2 - IterTime_ };
			}
			else
			{
				Icon_.lock()->Off();
			}
			Icon_.lock()->UpdateColor({ 0,0,0,0 }, Color);
		}
	}
	else
	{
		Foreground_.lock()->On();
		Background_.lock()->On();
	}
	Foreground_.lock()->UpdateLeftToRight(Value);

	//경고표시전 값이 업데이트 되는지 확인
	if (PrevValue_ < Value)
	{
		PrevValue_ = Value;
		IsUpdating_ = true;
	}

	//경고표시
	if (Value >= 1.5f && IsOver_ == true)
	{
		if (Icon_.lock()->IsUpdate() == false)
		{
			Icon_.lock()->On();
			//Icon_.lock()->UpdateColor({ 0,0,0,0 }, { 1,1,1,1 });
			Icon_.lock()->SetTexture("BurnWarning.png");
		}
		if (IsUpdating_ == true) //경고표시가 뜬 상태에서 플레이어가 들었을때의 예외처리
		{
			IterTime_ += _DeltaTime * Value * Value * 0.7f;
		}
		float4 Color;
		if (IterTime_ < 1.f)
		{
			Color = { 1.f,1.f,1.f,IterTime_ };
		}
		else if (IterTime_ >= 1.f && IterTime_ < 2.f)
		{
			Color = { 1.f,1.f,1.f,2 - IterTime_ };
		}
		else
		{
			IterTime_ = 0.f;
			Color = { 1.f,1.f,1.f,IterTime_ };
			//경고표시전 값이 업데이트 되는지 확인
			if (PrevValue_ < Value)
			{
				PrevValue_ = Value;
				IsUpdating_ = true;
			}
			else
			{
				IsUpdating_ = false;
			}
		}
		Icon_.lock()->UpdateColor({ 0,0,0,0 }, Color);
	}
}

void CookingBar::ChaseTarget()
{
	//Update Position
	float4 Pos = ChaseActor_.lock()->GetTransform().GetWorldPosition();
	float4 WantPos = GetLevel()->GetCameraActor(CAMERAORDER::MAINCAMERA)->GetCameraComponent()->GetWorldPositionToScreenPosition(Pos);
	float4 ScreenScale = GameEngineWindow::GetScale().Half();
	ScreenScale.y = -ScreenScale.y;
	WantPos = float4(WantPos.x, -WantPos.y, WantPos.z) - ScreenScale;
	WantPos.x = WantPos.x - WantPos.x * -0.02f;
	WantPos.y = WantPos.y - WantPos.y * -0.02f;
	WantPos += Offset_;
	GetTransform().SetLocalPosition(WantPos);
}

void CookingBar::End()
{
}