#include "PreCompile.h"
#include "RespawnUI.h"

RespawnUI::RespawnUI()
{
}

RespawnUI::~RespawnUI()
{
}

void RespawnUI::Init(const float4& _Pos, float* _Time)
{
	//if (_Time == nullptr)
	//{
	//	MsgBoxAssert("_Time이 Nullptr입니다.");
	//}
	Time_Iter_ = _Time;
	IsInit_ = true;

	float4 Pos = _Pos;
	float4 WantPos = GetLevel()->GetCameraActor(CAMERAORDER::MAINCAMERA)->GetCameraComponent()->GetWorldPositionToScreenPosition(Pos);
	float4 ScreenScale = GameEngineWindow::GetScale().Half();
	ScreenScale.y = -ScreenScale.y;
	WantPos = float4(WantPos.x, -WantPos.y, WantPos.z) - ScreenScale;
	WantPos.x = WantPos.x - WantPos.x * -0.02f;
	WantPos.y = WantPos.y - WantPos.y * -0.02f;
	GetTransform().SetLocalPosition(WantPos);
}

void RespawnUI::Start()
{
	Background_ = CreateComponent<OverCookedUIRenderer>();
	Background_.lock()->SetTexture("respawn_blue.png");
	Background_.lock()->SetScaleRatio(0.24f);
	Background_.lock()->ScaleToTexture();
	Background_.lock()->ChangeCamera(CAMERAORDER::USER7);
}

void RespawnUI::Update(float _DeltaTime)
{
	//if (IsInit_ == false || Time_Iter_ == nullptr)
	//{
	//	return;
	//}
}

void RespawnUI::End()
{
}