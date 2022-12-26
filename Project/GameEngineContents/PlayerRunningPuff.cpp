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
	Renderer.MulColor = float4{0.1,0.1,0.1,1};
	RunningPuffRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	RunningPuffRenderer_->SetOrder(10000000000000000);
	RunningPuffRenderer_->SetPivot(PIVOTMODE::CENTER);
	RunningPuffRenderer_->SetTexture("RunningPuff.png");
	RunningPuffRenderer_->ScaleToTexture();
	RunningPuffRenderer_->GetTransform().SetLocalPosition({ 0.0f ,50.0f,50.0f });
	//RunningPuffRenderer_->GetShaderResources().SetConstantBufferLink("PixelData", &Renderer, sizeof(PixelData));


	Death(3.0f);
}
void PlayerRunningPuff::Update(float _DeltaTime)
{
	Renderer.MulColor.a -= 1.0f * _DeltaTime;

	//GetTransform().SetAddWorldRotation(float4(0, 100, 0) * _DeltaTime);
	GetTransform().SetWorldRotation(float4::GetDegree3D(GetTransform().GetWorldPosition(), GetLevel()->GetMainCameraActorTransform().GetWorldPosition()));
}