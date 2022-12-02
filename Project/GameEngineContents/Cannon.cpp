#include "PreCompile.h"
#include "Cannon.h"

Cannon::Cannon() 
	: CannonBase_(nullptr)
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
	BaseRenderer->SetFBXMesh("Cannon_Base.fbx", "Texture", 0);
	BaseRenderer->GetTransform().SetWorldScale({ 100, 100, 100 });

	GetFBXMesh()->SetFBXMesh("m_dlc08_cannon_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	GetFBXMesh()->GetTransform().SetWorldMove({ 0, 0, 0 });

	GetCollisionObject()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

void Cannon::Update(float _DeltaTime)
{
}

