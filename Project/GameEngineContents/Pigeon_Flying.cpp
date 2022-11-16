#include "PreCompile.h"
#include "Pigeon_Flying.h"

Pigeon_Flying::Pigeon_Flying() 
{
}

Pigeon_Flying::~Pigeon_Flying() 
{
}

void Pigeon_Flying::Start()
{
	GamePlayMapObject::Start();
	GetAnimationFBXMesh()->GetTransform().SetWorldScale({ 140.f, 140.f, 140.f });
	GetAnimationFBXMesh()->SetFBXMesh("m_city_pigeon_01.fbx", "TextureAnimation", 0);	// Flying
	GetAnimationFBXMesh()->CreateFBXAnimation("Fly", "m_city_pigeon_01.fbx");
	GetAnimationFBXMesh()->ChangeAnimation("Fly");
	GetCollisionObject()->Off();
}

void Pigeon_Flying::Update(float _DeltaTime)
{
}

