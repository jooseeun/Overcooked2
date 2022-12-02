#include "PreCompile.h"
#include "Oven.h"

Oven::Oven() 
	: Door_(nullptr)
{
}

Oven::~Oven() 
{
}

void Oven::Start()
{
	GamePlayStaticObject::Start();

	// ¿Àºì ¹®
	Door_ = GetLevel()->CreateActor<GameEngineActor>();
	Door_->SetParent(shared_from_this());

	std::shared_ptr<GameEngineFBXStaticRenderer> DoorRenderer = Door_->CreateComponent<GameEngineFBXStaticRenderer>();
	DoorRenderer->SetFBXMesh("OvenDoor.fbx", "Texture");
	DoorRenderer->GetTransform().SetWorldScale({ 100, 100, 100 });

	// ¿Àºì
	GetFBXMesh()->SetFBXMesh("Oven.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

void Oven::Update(float _Delta)
{
}

