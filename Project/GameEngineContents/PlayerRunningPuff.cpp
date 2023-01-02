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
	RunningPuffRenderer_->GetPixelDatas(0).MulColor.a = 0.2f;
	RunningPuffRenderer_->GetTransform().SetLocalRotation({ 80,120,0 });
	OriginalScale_ = RunningPuffRenderer_->GetTransform().GetLocalScale();
	RunningPuffRenderer_->GetTransform().SetLocalScale(RunningPuffRenderer_->GetTransform().GetLocalScale()* Scale_);

	//PixelData& IdleRender = RunningPuffRenderer_->GetPixelDatas(0);
	//IdleRender.MulColor.a = 0.2f;
	//IdleRender.AlphaColor.a = 0.2f;

	float DeathTime = GameEngineRandom::MainRandom.RandomFloat(0.5f, 0.8f);
	RunningPuffRenderer_->SetRenderingOrder(99);

	RunningPuffRenderer_->GetPixelDatas(0).AlphaFlag = 1;
	RunningPuffRenderer_->GetPixelDatas(0).MulColor.a = 0.2f;

	//PixelData& Renderer = RunningPuffRenderer_->GetPixelDatas(0);
	//Renderer.MulColor.a -= 0.3f;
	
	float DeathTime = GameEngineRandom::MainRandom.RandomFloat(1.0f, 3.0f);
	Death(DeathTime);
}
void PlayerRunningPuff::Update(float _DeltaTime)
{


	//GetTransform().SetAddWorldRotation(float4(0, 100, 0) * _DeltaTime);
	GetTransform().SetWorldRotation(float4::GetDegree3D(GetTransform().GetWorldPosition(), GetLevel()->GetMainCameraActorTransform().GetWorldPosition()));
}