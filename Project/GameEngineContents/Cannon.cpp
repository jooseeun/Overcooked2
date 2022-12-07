#include "PreCompile.h"
#include "Cannon.h"

Cannon::Cannon() 
	: CannonBase_(nullptr)
	, CurState_(CannonState::Max)
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

	GetFBXMesh()->SetFBXMesh("m_dlc08_cannon_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	GetFBXMesh()->GetTransform().SetWorldMove({ 0, 100, 0 });
	GetFBXMesh()->GetTransform().SetWorldRotation({90, 0, 90});

	GetCollisionObject()->ChangeOrder(CollisionOrder::Map_Cannon);
	GetCollisionObject()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

void Cannon::Update(float _DeltaTime)
{
	// Idle 상태에서 플레이어와 충돌 + 키 입력 시 => Ready
	// Button => On

	// Ready 상태에서 버튼과 플레이어 충돌 + 키 입력 시 => Shoot
	// Button => Off

	// Shoot 끝난 후 => Idle
}

void Cannon::IdleStart(const StateInfo& _Info)
{
}

void Cannon::LIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Cannon::ReadyStart(const StateInfo& _Info)
{
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

