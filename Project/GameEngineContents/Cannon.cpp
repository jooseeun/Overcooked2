#include "PreCompile.h"
#include "Cannon.h"
#include "Button.h"
#include "Player.h"

Cannon::Cannon() 
	: CurState_(CannonState::Max)
	, ShootAngle_(-190.f)
	, MaxAngle_(-35.f)
	, CurAngle_(0.f)
	, IsShoot_(false)
{
}

Cannon::~Cannon() 
{
}

void Cannon::Start()
{
	
	BaseRenderer = CreateComponent<GameEngineFBXStaticRenderer>();
	BaseRenderer->SetFBXMesh("Cannon_Base.fbx", "Texture");
	BaseRenderer->GetTransform().SetWorldScale({ 100, 100, 100 });

	Mesh_Object_ = CreateComponent<GameEngineFBXStaticRenderer>("Mesh_Object");
	Mesh_Object_->SetFBXMesh("m_dlc08_cannon_02.fbx", "Texture");
	Mesh_Object_->GetTransform().SetWorldScale({ 100, 100, 100 });
	Mesh_Object_->GetTransform().SetWorldMove({ 0, 100, 0 });

	Collision_Object_ = CreateComponent<GameEngineCollision>("Collision_Object");
	Collision_Object_->ChangeOrder(CollisionOrder::Map_Cannon);
	Collision_Object_->GetTransform().SetWorldScale({ 100, 100, 100 });

	Button_ = GetLevel()->CreateActor<Button>();
	Button_->GetTransform().SetWorldMove({0.f, 0.f, 122.f});
	Button_->SetParent(shared_from_this());

	StateManager.CreateStateMember("Idle"
		, std::bind(&Cannon::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Cannon::IdleStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("Ready"
		, std::bind(&Cannon::ReadyUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Cannon::ReadyStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("ReadyToIdle"
		, std::bind(&Cannon::ReadyToIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Cannon::ReadyToIdleStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("Shoot"
		, std::bind(&Cannon::ShootUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Cannon::ShootStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("ShootToIdle"
		, std::bind(&Cannon::ShootToIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Cannon::ShootToIdleStart, this, std::placeholders::_1)
	);

	StateManager.ChangeState("Idle");
}

void Cannon::Update(float _DeltaTime)
{
	// Idle 상태에서 플레이어와 충돌 + 키 입력 시 => Ready
	// Button => On

	// Ready 상태에서 버튼과 플레이어 충돌 + 키 입력 시 => Shoot
	// Button => Off

	// Shoot 끝난 후 => Idle

	//if (Player_ != nullptr)
	//{
	//	//Player_->CannonZAngle_ = CurAngle_; 각도 이렇게 넣어주세요
	//}
	CurAngle_ = Mesh_Object_->GetTransform().GetWorldRotation().z;
	StateManager.Update(_DeltaTime);

	DebugOn();
}

void Cannon::IdleStart(const StateInfo& _Info)
{
	CurState_ = CannonState::Idle;
}

void Cannon::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (nullptr != Player_)
	{
		StateManager.ChangeState("Ready");
	}
}

void Cannon::ReadyStart(const StateInfo& _Info)
{
	CurState_ = CannonState::Ready;
	Button_->SwitchButtonState();
}

void Cannon::ReadyUpdate(float _DeltaTime, const StateInfo& _Info)
{
	/*if (Player_->IsCannon_ == false)
	{
		ResetPlayer();
		StateManager.ChangeState("ReadyToIdle");
	}*/

	if (nullptr == Player_)
	{
		StateManager.ChangeState("ReadyToIdle");
	}
	if (true == Button_->CheckButtonPressedState())
	{
		StateManager.ChangeState("Shoot");
	}

	if (CurAngle_ > MaxAngle_)
	{
		Mesh_Object_->GetTransform().SetAddWorldRotation(float4{ 0.f, 0.f, ShootAngle_ } *_DeltaTime);;
	}

}

void Cannon::ReadyToIdleStart(const StateInfo& _Info)
{
	CurState_ = CannonState::ReadyToIdle;
	Button_->SwitchButtonState();
}

void Cannon::ReadyToIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (CurAngle_ >= 0.f)
	{
		StateManager.ChangeState("Idle");
	}
	else
	{
		Mesh_Object_->GetTransform().SetAddWorldRotation(float4{ 0.f, 0.f, -ShootAngle_ } * _DeltaTime);
	}
}

void Cannon::ShootStart(const StateInfo& _Info)
{
	CurState_ = CannonState::Shoot;
	//Player_->IsCannonFly_ = true;
	Button_->SwitchButtonState();
}

void Cannon::ShootUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (_Info.StateTime > 2.f)
	{
		StateManager.ChangeState("ShootToIdle");
	}
}

void Cannon::ShootToIdleStart(const StateInfo& _Info)
{
	CurState_ = CannonState::ShootToIdle;
}

void Cannon::ShootToIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (CurAngle_ >= 0.f)
	{
		StateManager.ChangeState("Idle");
	}
	else
	{
		Mesh_Object_->GetTransform().SetAddWorldRotation(float4{ 0.f, 0.f, -ShootAngle_ } *_DeltaTime);
	}
}

