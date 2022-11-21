#include "PreCompile.h"
#include "Rail.h"

Rail::Rail() 
{
}

Rail::~Rail() 
{
}

void Rail::Start()
{
	GamePlayStaticObject::Start();

	GetFBXMesh()->SetFBXMesh("m_sk_conveyor_belt_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });

	GetCollisionObject()->GetTransform().SetWorldScale({ 120, 50, 120 });
	GetCollisionObject()->GetTransform().SetWorldMove({ 0, 25, 0 });
}

