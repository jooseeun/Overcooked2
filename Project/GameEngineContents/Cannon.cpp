#include "PreCompile.h"
#include "Cannon.h"
#include "Button.h"
#include "Player.h"

Cannon::Cannon() 
	: CurState_(CannonState::Max)
	, ShootAngle_(-250.f)
	, MaxAngle_(-40.f)
	, CurAngle_(0.f)
	, IsShoot_(false)
	, IsCounterReaction_(false)
	, IsMoveDone_(false)
	, ReactCount_(0)
	, Power_(0.f)
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

	CurAngle_ = Mesh_Object_->GetTransform().GetWorldRotation().z;
	if (Player_ != nullptr)
	{
		Player_->CannonZAngle_ = CurAngle_; 
	}

	StateManager.Update(_DeltaTime);

	DebugOn();
}

void Cannon::IdleStart(const StateInfo& _Info)
{
	if (Player_ == nullptr)
	{
		return;
	}
	CurAngle_ = 0.f;
	CurState_ = CannonState::Idle;
}

void Cannon::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (Player_ == nullptr)
	{
		return;
	}

	Mesh_Object_->GetTransform().SetWorldRotation(CurAngle_);

	if (true == Player_->IsCannon_)
	{
		StateManager.ChangeState("Ready");
	}
}

void Cannon::ReadyStart(const StateInfo& _Info)
{
	CurState_ = CannonState::Ready;
	Button_->IsReady_ = true;
	IsMoveDone_ = false;
	IsCounterReaction_ = false;
}

void Cannon::ReadyUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// 플레이어가 내렸다
	if (false == Player_->IsCannon_)
	{
		ResetPlayer();
		StateManager.ChangeState("ReadyToIdle");
	}
	// 버튼이 눌렸다
	else if (true == Button_->CheckButtonPressedState() && true == Player_->IsCannon_)
	{
		StateManager.ChangeState("Shoot");
	}
	//else if (_Info.StateTime > 2.f && true == Player_->IsCannon_)
	//{
	//	StateManager.ChangeState("Shoot");
	//}

	if (true == IsMoveDone_)
	{
		return;
	}

	if (CurAngle_ <= MaxAngle_)
	{
		IsCounterReaction_ = true;
	}
	if (CurAngle_ > MaxAngle_ && false == IsCounterReaction_)
	{
		Mesh_Object_->GetTransform().SetAddWorldRotation(float4{ 0.f, 0.f, ShootAngle_ } *_DeltaTime);
	}
	else if (true == IsCounterReaction_)
	{
		if (CurAngle_ >= MaxAngle_ + 8.f)
		{
			IsCounterReaction_ = false;
			IsMoveDone_ = true;
		}
		Mesh_Object_->GetTransform().SetAddWorldRotation(float4{ 0.f, 0.f, 100.f } *_DeltaTime);
	}
}

void Cannon::ReadyToIdleStart(const StateInfo& _Info)
{
	CurState_ = CannonState::ReadyToIdle;
	Button_->IsReady_ = false;
	IsMoveDone_ = false;
	IsCounterReaction_ = false;
	//ReactCount_ = 3;
	//Power_ = 70.f;
}

void Cannon::ReadyToIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	//if (CurAngle_ >= 0.f)
	//{
	//	StateManager.ChangeState("Idle");
	//}
	//else
	//{
	//	Mesh_Object_->GetTransform().SetAddWorldRotation(float4{ 0.f, 0.f, -ShootAngle_ } * _DeltaTime);
	//}

	if (nullptr != Player_)
	{
		if (true == Player_->IsCannon_)
		{
			StateManager.ChangeState("Ready");
		}
	}

	CounterReaction(_DeltaTime);
}

void Cannon::ShootStart(const StateInfo& _Info)
{
	CurState_ = CannonState::Shoot;
	Player_->IsCannon_ = false;
	Player_->IsCannonFly_ = true;
	Button_->IsReady_ = false;
	Button_->SetButtonUnPressed();
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
	IsMoveDone_ = false;
	IsCounterReaction_ = false;
	//ReactCount_ = 3;
	//Power_ = 70.f;
}

void Cannon::ShootToIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	//if (CurAngle_ >= 0.f)
	//{
	//	StateManager.ChangeState("Idle");
	//}
	//else
	//{
	//	Mesh_Object_->GetTransform().SetAddWorldRotation(float4{ 0.f, 0.f, -ShootAngle_ } *_DeltaTime);
	//}

	CounterReaction(_DeltaTime);
}

void Cannon::CounterReaction(float _DeltaTime)
{
	//if (ReactCount_ == 0)
	//{
	//	StateManager.ChangeState("Idle");
	//}

	//if (CurAngle_ > MaxAngle_ && false == IsCounterReaction_)
	//{
	//	if (CurAngle_ >= 0.f)
	//	{
	//		IsCounterReaction_ = true;
	//	}

	//	Mesh_Object_->GetTransform().SetAddWorldRotation(float4{ 0.f, 0.f, -ShootAngle_ } *_DeltaTime);
	//}
	//else if (true == IsCounterReaction_)
	//{
	//	Power_ += 300.f * _DeltaTime;
	//	if (CurAngle_ <= 0.f && CurAngle_ >= -10.f)
	//	{
	//		Mesh_Object_->GetTransform().SetAddWorldRotation(float4{ 0.f, 0.f, Power_ } *_DeltaTime);
	//	}
	//	else if (CurAngle_ >= 2.f)
	//	{
	//		Mesh_Object_->GetTransform().SetAddWorldRotation(float4{ 0.f, 0.f, -Power_ } *_DeltaTime);
	//		ReactCount_ -= 1;
	//	}
	//}

	if (true == IsMoveDone_)
	{
		StateManager.ChangeState("Idle");
		return;
	}

	if (CurAngle_ >= 0.f)
	{
		IsCounterReaction_ = true;
	}
	if (true == IsCounterReaction_)
	{
		if (CurAngle_ >= 0.f)
		{
			IsCounterReaction_ = false;
			IsMoveDone_ = true;
		}
		Mesh_Object_->GetTransform().SetAddWorldRotation(float4{ 0.f, 0.f, -100.f } *_DeltaTime);
	}
	else
	{
		Mesh_Object_->GetTransform().SetAddWorldRotation(float4{ 0.f, 0.f, -ShootAngle_ } *_DeltaTime);
	}
}