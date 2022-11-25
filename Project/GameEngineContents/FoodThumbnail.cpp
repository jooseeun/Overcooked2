#include "PreCompile.h"
#include "FoodThumbnail.h"

#include "GlobalGameData.h"
#include "UIDebugGUI.h"

FoodThumbnail::FoodThumbnail()
{
}

FoodThumbnail::~FoodThumbnail()
{
}

void FoodThumbnail::Start()
{
	//추후에 Main카메라 옮기면서 User7카메라도 이동시켜달라고하기
	std::string _FileName = "prawn_Icon.png";
	SingleThumbnail_ = CreateComponent<OverCookedUIRenderer>();
	SingleThumbnail_->SetTexture(_FileName);
	SingleThumbnail_->SetScaleRatio(0.34f);
	SingleThumbnail_->ScaleToTexture();
	SingleThumbnail_->ChangeCamera(CAMERAORDER::USER7);
	//SingleThumbnail_->Off();

	UIDebugGUI::Main_->AddMutableValue("DebugValue", &DebugValue_);
}

void FoodThumbnail::Update(float _DeltaTime)
{
	//if(ChaseActor_ == nullptr)
	if (ChaseActor_ == nullptr)
	{
		return;
	}
	if (ChaseActor_->IsDeath() == true)
	{
		Death();
	}

	//Update Position
	float4 Pos = ChaseActor_->GetTransform().GetWorldPosition();
	float4 WantPos = GetLevel()->GetCameraActor(CAMERAORDER::MAINCAMERA)->GetCameraComponent()->GetWorldPositionToScreenPosition(Pos);
	float4 ScreenScale = GameEngineWindow::GetScale().Half();
	ScreenScale.y = -ScreenScale.y;
	WantPos = float4(WantPos.x, -WantPos.y, WantPos.z) - ScreenScale;
	WantPos.x = WantPos.x - WantPos.x * DebugValue_;
	WantPos.y = WantPos.y - WantPos.y * DebugValue_;
	WantPos += Offset_;
	GetTransform().SetLocalPosition(WantPos);

	//float4 Pos = ChaseActor_->GetTransform().GetWorldPosition() + Offset_;
	//float4 CameraPos = GetLevel()->GetCameraActor(CAMERAORDER::MAINCAMERA)->GetTransform().GetWorldPosition();

	//float4 Move = Pos - CameraPos;
	//GetTransform().SetLocalPosition(Move);
}

void FoodThumbnail::End()
{
}

void FoodThumbnail::LinkObject(std::shared_ptr<GameEngineActor> _Actor, const float4& _Offset)
{
	ChaseActor_ = _Actor;
	Offset_ = _Offset;
}