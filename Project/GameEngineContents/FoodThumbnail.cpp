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
	//���Ŀ� Mainī�޶� �ű�鼭 User7ī�޶� �̵����Ѵ޶���ϱ�
	std::string _FileName = "prawn_Icon.png";
	SingleThumbnail_ = CreateComponent<OverCookedUIRenderer>();
	SingleThumbnail_->SetTexture(_FileName);
	SingleThumbnail_->SetScaleRatio(0.6f);
	SingleThumbnail_->ScaleToTexture();
	SingleThumbnail_->ChangeCamera(CAMERAORDER::USER7);
	//SingleThumbnail_->Off();

	UIDebugGUI::Main_->AddTransform("Thumbnail", &GetTransform());
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
	float4 Pos = ChaseActor_->GetTransform().GetWorldPosition() + Offset_;
	//SingleThumbnail_->GetTransform().SetWorldRotation(GetLevel()->GetCameraActor(CAMERAORDER::USER7)->GetTransform().GetWorldRotation());
	float4 WantPos = GetLevel()->GetCameraActor(CAMERAORDER::USER7)->GetCameraComponent()->GetWorldPositionToScreenPosition(Pos);
	GetTransform().SetWorldPosition(WantPos);
}

void FoodThumbnail::End()
{
}

void FoodThumbnail::LinkObject(std::shared_ptr<GameEngineActor> _Actor, const float4& _Offset)
{
	ChaseActor_ = _Actor;
	Offset_ = _Offset;
}