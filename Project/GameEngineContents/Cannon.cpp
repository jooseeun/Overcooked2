#include "PreCompile.h"
#include "Cannon.h"

Cannon::Cannon() 
	: CannonBase_(nullptr)
	, CurState_(CannonState::Max)
	, Interaction_(false)
	, ZAngle_({0.f, 0.f, -30.f})
{
}

Cannon::~Cannon() 
{
}

void Cannon::Start()
{
	GamePlayStaticObject::Start();

	CannonBase_ = GetLevel()->CreateActor<GameEngineActor>();
	CannonBase_->SetParent(shared_from_this());

	std::shared_ptr<GameEngineFBXStaticRenderer> BaseRenderer = CannonBase_->CreateComponent<GameEngineFBXStaticRenderer>();
	BaseRenderer->SetFBXMesh("Cannon_Base.fbx", "Texture");
	BaseRenderer->GetTransform().SetWorldScale({ 100, 100, 100 });

	GetFBXMesh()->SetFBXMesh("m_dlc08_cannon_02.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	GetFBXMesh()->GetTransform().SetWorldMove({ 0, 100, 0 });

	GetCollisionObject()->ChangeOrder(CollisionOrder::Map_Cannon);
	GetCollisionObject()->GetTransform().SetWorldScale({ 100, 100, 100 });

	StateManager.CreateStateMember("Idle"
		, std::bind(&Cannon::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Cannon::IdleStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("Ready"
		, std::bind(&Cannon::ReadyUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Cannon::ReadyStart, this, std::placeholders::_1)
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
	GetFBXMesh()->GetTransform().SetAddWorldRotation( ZAngle_  *_DeltaTime);
}

void Cannon::IdleStart(const StateInfo& _Info)
{
}

void Cannon::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == Interaction_)
	{
		StateManager.ChangeState("Ready");
	}
}

void Cannon::ReadyStart(const StateInfo& _Info)
{
	ZAngle_.z = 30.f;

}

void Cannon::ReadyUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Cannon::ShootStart(const StateInfo& _Info)
{
}

void Cannon::ShootUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Cannon::ShootToIdleStart(const StateInfo& _Info)
{
}

void Cannon::ShootToIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

