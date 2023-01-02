#include "PreCompile.h"
#include "PlayerRunningPuff.h"

PlayerRunningPuff::PlayerRunningPuff()
	:RunningPuffRenderer_(nullptr)
	, Scale_(0.5f)
{
}

PlayerRunningPuff::~PlayerRunningPuff()
{

}

void PlayerRunningPuff::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });

	RunningPuffRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();

	RunningPuffRenderer_->SetFBXMesh("RunPuff.fbx", "Texture");
	//RunningPuffRenderer_->GetPixelDatas(0).AlphaFlag = true;
	RunningPuffRenderer_->SetRenderingOrder(99);
	RunningPuffRenderer_->GetPixelDatas(0).AlphaFlag = 1;
	RunningPuffRenderer_->GetPixelDatas(0).MulColor.a = 0.7;
	RunningPuffRenderer_->GetTransform().SetLocalRotation({ 80,120,0 });
	OriginalScale_ = RunningPuffRenderer_->GetTransform().GetLocalScale();
	RunningPuffRenderer_->GetTransform().SetLocalScale(RunningPuffRenderer_->GetTransform().GetLocalScale()* Scale_);

	
	float DeathTime = GameEngineRandom::MainRandom.RandomFloat(0.5f, 1.2f);
	//Death(DeathTime);
}
void PlayerRunningPuff::Update(float _DeltaTime)
{
	if (RunningPuffRenderer_->GetPixelDatas(0).MulColor.a > 0.01f)
	{
		RunningPuffRenderer_->GetPixelDatas(0).MulColor.a -= 1.0f * _DeltaTime;
	}
	
	if (GetTransform().GetWorldScale().x > 0.0f)
	{
		GetTransform().SetWorldScale(GetTransform().GetWorldScale() - float4{ 0.7f,0.7f ,0.7f } *GameEngineTime::GetDeltaTime());
	}
	GetTransform().SetWorldRotation(float4::GetDegree3D(GetTransform().GetWorldPosition(), GetLevel()->GetMainCameraActorTransform().GetWorldPosition()));
}