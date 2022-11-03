#include "PreCompile.h"
#include "GlobalMouseInput.h"
#include "MouseInputWindow.h"

GlobalMouseInput::GlobalMouseInput()
	: MouseWindow_(nullptr)
	, Collision_(nullptr)
	, StartCollision_(nullptr)
	, GoalCollision_(nullptr)
	, NearActor_(nullptr)
{
}

GlobalMouseInput::~GlobalMouseInput()
{
}

void GlobalMouseInput::Start()
{
	MouseWindow_ = MapEditorGUI::CreateGUIWindow<MouseInputWindow>("MouseInput", nullptr);
	MouseWindow_->Off();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetWorldScale({ 0.1f, 0.1f, 10000 });
	Collision_->ChangeOrder(CollisionOrder::Mouse);

	StartCollision_ = CreateComponent<GameEngineCollision>();
	StartCollision_->GetTransform().SetWorldScale({ 0.1f, 0.1f, 0.1f });
	StartCollision_->ChangeOrder(CollisionOrder::Max);
	StartCollision_->SetDebugSetting(CollisionType::CT_AABB, { 1.0f, 1.0f, 0.0f, 0.5f });
	StartCollision_->Off();

	GoalCollision_ = CreateComponent<GameEngineCollision>();
	GoalCollision_->GetTransform().SetWorldScale({ 10, 10, 10 });
	GoalCollision_->ChangeOrder(CollisionOrder::Max);
	GoalCollision_->SetDebugSetting(CollisionType::CT_AABB, { 1.0f, 1.0f, 0.0f, 1.0f });
}

void GlobalMouseInput::Update(float _Delta)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		StartCollision_->GetTransform().SetWorldScale({ 10, 10, 10 });
		return;
	}

	StartCollision_->GetTransform().SetWorldScale({ 0.1f, 0.1f, 0.1f });
	TransformUpdate(_Delta);
	ClickUpdate(_Delta);
}

void GlobalMouseInput::TransformUpdate(float _Delta)
{
	GameEngineTransform& MainCameraTransform = GetLevel()->GetMainCameraActorTransform();
	float4 AddPos = (MainCameraTransform.GetForwardVector() * 1350 + GetLevel()->GetMainCamera()->GetMouseMyPosition()) * 0.1f;
	float4 StartPos = MainCameraTransform.GetWorldPosition() + MainCameraTransform.GetForwardVector();
	float4 GoalPos = MainCameraTransform.GetWorldPosition() + AddPos;
	while (GoalPos.y >= 0 && AddPos.y < 0)
	{
		GoalPos += AddPos;
	}

	Collision_->GetTransform().SetWorldPosition((StartPos + GoalPos) * 0.5f);
	Collision_->GetTransform().SetWorldRotation(float4::GetDegree3D(StartPos, GoalPos));
	Collision_->GetTransform().SetWorldScale({10.1f, 10.1f, (StartPos - GoalPos).Length()});

	StartCollision_->GetTransform().SetWorldPosition(StartPos);
	GoalCollision_->GetTransform().SetWorldPosition(GoalPos);
}

void GlobalMouseInput::ClickUpdate(float _Delta)
{
	if (true == GameEngineInput::GetInst()->IsDownKey("LeftMouse"))
	{
		Collision_->SetDebugSetting(CollisionType::CT_AABB, { 0.0f, 1.0f, 0.0f, 0.5f });
		Collision_->IsCollision(CollisionOrder::Default, std::bind(&GlobalMouseInput::CollisionCheck, this, std::placeholders::_1, std::placeholders::_2));
	}
	else if (true == GameEngineInput::GetInst()->IsUpKey("LeftMouse"))
	{
		Collision_->SetDebugSetting(CollisionType::CT_AABB, { 1.0f, 0.0f, 0.0f, 0.5f });
	}
}

CollisionReturn GlobalMouseInput::CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	GameEngineActor* OtherActor = _Other->GetActor();
	if (nullptr == OtherActor)
	{
		return CollisionReturn::Break;
	}

	if (nullptr == NearActor_)
	{
		NearActor_ = OtherActor;
		MouseWindow_->SetMouseInput(this);
		MouseWindow_->On();
	}
	else
	{
		float Distance1 = (GetTransform().GetWorldPosition() - OtherActor->GetTransform().GetWorldPosition()).Length();
		float Distance2 = (GetTransform().GetWorldPosition() - NearActor_->GetTransform().GetWorldPosition()).Length();
		if (Distance1 < Distance2)
		{
			NearActor_ = OtherActor;
			MouseWindow_->SetMouseInput(this);
			MouseWindow_->On();
		}
	}

	return CollisionReturn::ContinueCheck;
}
