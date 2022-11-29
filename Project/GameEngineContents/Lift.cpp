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
	GetCollisionObject()->GetTransform().SetLocalPosition({ GetTransform().GetWorldPosition()});
}

void Lift::Update(float _DeltaTime)
{
}

