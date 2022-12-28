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
	RunningPuffRenderer_->GetTransform().SetLocalRotation({ 80,120,0 });
	OriginalScale_ = RunningPuffRenderer_->GetTransform().GetLocalScale();
	RunningPuffRenderer_->GetTransform().SetLocalScale(RunningPuffRenderer_->GetTransform().GetLocalScale()* Scale_);
	//RunningPuffRenderer_->SetRenderingOrder(99);
	//RunningPuffRenderer_->GetPixelData().MulColor.a = 0.8f;
	PixelData& Renderer = RunningPuffRenderer_->GetPixelDatas(0);
	Renderer.MulColor.a -= 0.3f;
	
	float DeathTime = GameEngineRandom::MainRandom.RandomFloat(1.0f, 3.0f);
	Death(DeathTime);
}
void PlayerRunningPuff::Update(float _DeltaTime)
{
	RunningPuffRenderer_->GetPixelData().MulColor.a -= 0.2f* _DeltaTime;

	//GetTransform().SetAddWorldRotation(float4(0, 100, 0) * _DeltaTime);
	GetTransform().SetWorldRotation(float4::GetDegree3D(GetTransform().GetWorldPosition(), GetLevel()->GetMainCameraActorTransform().GetWorldPosition()));
}