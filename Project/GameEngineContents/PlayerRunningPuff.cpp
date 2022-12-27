#include "PreCompile.h"
#include "PlayerRunningPuff.h"

PlayerRunningPuff::PlayerRunningPuff() 
	:RunningPuffRenderer_(nullptr)
{
}

PlayerRunningPuff::~PlayerRunningPuff() 
{
}

void PlayerRunningPuff::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });
	RunningPuffRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	RunningPuffRenderer_->SetPivot(PIVOTMODE::CENTER);
	RunningPuffRenderer_->SetTexture("RunningPuff_gray.png");
	RunningPuffRenderer_->SetRenderingOrder(99);
	RunningPuffRenderer_->GetPixelData().MulColor.a = 0.8f;


	Death(2.0f);
}
void PlayerRunningPuff::Update(float _DeltaTime)
{
	RunningPuffRenderer_->GetPixelData().MulColor.a -= 0.2f* _DeltaTime;

	//GetTransform().SetAddWorldRotation(float4(0, 100, 0) * _DeltaTime);
	GetTransform().SetWorldRotation(float4::GetDegree3D(GetTransform().GetWorldPosition(), GetLevel()->GetMainCameraActorTransform().GetWorldPosition()));
}