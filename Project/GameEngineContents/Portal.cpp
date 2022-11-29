#include "PreCompile.h"
#include "Portal.h"

Portal::Portal() 
{
}

Portal::~Portal() 
{
}

void Portal::Start()
{
	GamePlayMapObject::Start();
	GetCollisionObject()->GetTransform().SetLocalPosition({ GetTransform().GetWorldPosition() });
}

void Portal::Update(float _DeltaTime)
{
}

