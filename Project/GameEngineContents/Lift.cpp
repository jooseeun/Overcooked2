#include "PreCompile.h"
#include "Lift.h"

Lift::Lift() 
{
}

Lift::~Lift() 
{
}

void Lift::Start()
{
	GamePlayFloor::Start();
	GetCollisionObject()->GetTransform().SetLocalPosition({ GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, -49.f});
}

void Lift::Update(float _DeltaTime)
{
}

