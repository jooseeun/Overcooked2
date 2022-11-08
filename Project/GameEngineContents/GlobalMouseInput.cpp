#include "PreCompile.h"
#include "GlobalMouseInput.h"
#include "MouseInputWindow.h"

GlobalMouseInput::GlobalMouseInput()
	: MouseWindow_(nullptr)
	, Collision_(nullptr)
	, StartCollision_(nullptr)
	, GoalCollision_(nullptr)
	, NearTransform_(nullptr)
	, IsUI_(false)
{
}

GlobalMouseInput::~GlobalMouseInput()
{
}

void GlobalMouseInput::Start()
{
	IsUI_ = true;
	MouseWindow_ = MapEditorGUI::CreateGUIWindow<MouseInputWindow>("MouseInput", nullptr);
	MouseWindow_->Off();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetWorldScale({ 0.1f, 0.1f, 10000 });
	Collision_->ChangeOrder(CollisionOrder::Mouse);
	Collision_->SetDebugSetting(CollisionType::CT_AABB, { 1.0f, 1.0f, 0.0f, 0.1f });

	StartCollision_ = CreateComponent<GameEngineCollision>();
	StartCollision_->GetTransform().SetWorldScale({ 0.1f, 0.1f, 0.1f });
	StartCollision_->GetTransform().SetWorldScale({ 10, 10, 10 });
	StartCollision_->ChangeOrder(CollisionOrder::Max);
	StartCollision_->SetDebugSetting(CollisionType::CT_AABB, { 1.0f, 1.0f, 0.0f, 0.5f });
	//StartCollision_->Off();

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
		StartCollision_->On();
		return;
	}

	StartCollision_->GetTransform().SetWorldScale({ 0.1f, 0.1f, 0.1f });
	TransformUpdate(_Delta);
	ClickUpdate(_Delta);
}

void GlobalMouseInput::TransformUpdate(float _Delta)
{
	float4 AddPos;
	float4 StartPos;
	float4 GoalPos;

	if (true == IsUI_)
	{
		GameEngineTransform& CameraTransform = GetLevel()->GetUICameraActorTransform();
		AddPos = (CameraTransform.GetForwardVector() * 1350 + GetLevel()->GetMainCamera()->GetMouseMyPosition()) * 0.1f;
		StartPos = CameraTransform.GetWorldPosition() + CameraTransform.GetForwardVector();
		GoalPos = CameraTransform.GetWorldPosition() + AddPos * 10;
		while (GoalPos.z <= 1000)
		{
			GoalPos += AddPos;
		}

		int a = 0;
	}
	else
	{
		GameEngineTransform& CameraTransform = GetLevel()->GetMainCameraActorTransform();
		AddPos = (CameraTransform.GetForwardVector() * 1350 + GetLevel()->GetMainCamera()->GetMouseMyPositionWithRotation()) * 0.1f;
		StartPos = CameraTransform.GetWorldPosition() + CameraTransform.GetForwardVector();
		GoalPos = CameraTransform.GetWorldPosition() + AddPos * 100;
		while (GoalPos.y >= 0 && AddPos.y < 0)
		{
			GoalPos += AddPos;
		}
	}

	Collision_->GetTransform().SetWorldPosition((StartPos + GoalPos) * 0.5f);
	Collision_->GetTransform().SetWorldRotation(float4::GetDegree3D(StartPos, GoalPos));
	Collision_->GetTransform().SetWorldScale({ 10.1f, 10.1f, (StartPos - GoalPos).Length() });

	MouseWindow_->SetMouseRotate(float4::GetDegree3D(StartPos, GoalPos));

	StartCollision_->GetTransform().SetWorldPosition(StartPos);
	GoalCollision_->GetTransform().SetWorldPosition(GoalPos);
}

void GlobalMouseInput::ClickUpdate(float _Delta)
{
	if (true == GameEngineInput::GetInst()->IsDownKey("LeftMouse"))
	{
		Collision_->SetDebugSetting(CollisionType::CT_AABB, { 0.0f, 1.0f, 0.0f, 0.1f });
		Collision_->IsCollision(CollisionOrder::Default, std::bind(&GlobalMouseInput::CollisionCheck, this, std::placeholders::_1, std::placeholders::_2));
	}
	else if (true == GameEngineInput::GetInst()->IsUpKey("LeftMouse"))
	{
		Collision_->SetDebugSetting(CollisionType::CT_AABB, { 1.0f, 0.0f, 0.0f, 0.1f });
	}
}

CollisionReturn GlobalMouseInput::CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	GameEngineTransform* OtherTransform = _Other->GetTransform().GetParentTransform();
	if (nullptr == OtherTransform)
	{
		return CollisionReturn::Break;
	}

	if (nullptr == NearTransform_)
	{
		NearTransform_ = OtherTransform;
		MouseWindow_->SetMouseInput(this);
		MouseWindow_->On();
	}
	else
	{
		float4 CameraPos;
		if (true == IsUI_)
		{
			CameraPos = GetLevel()->GetUICameraActorTransform().GetWorldPosition();
		}
		else
		{
			CameraPos = GetLevel()->GetMainCameraActorTransform().GetWorldPosition();
		}
		float Distance1 = (CameraPos - OtherTransform->GetWorldPosition()).Length();
		float Distance2 = (CameraPos - NearTransform_->GetWorldPosition()).Length();
		if (Distance1 < Distance2)
		{
			NearTransform_ = OtherTransform;
			MouseWindow_->SetMouseInput(this);
			MouseWindow_->On();
		}
	}

	return CollisionReturn::ContinueCheck;
}
