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
	}
	else
	{
		Foreground_.lock()->On();
		Background_.lock()->On();
	}
	Foreground_.lock()->UpdateLeftToRight(Value);
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