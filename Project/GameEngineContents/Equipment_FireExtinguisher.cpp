#include "PreCompile.h"
#include "Equipment_FireExtinguisher.h"

Equipment_FireExtinguisher::Equipment_FireExtinguisher() 
{
}

Equipment_FireExtinguisher::~Equipment_FireExtinguisher() 
{
}

void Equipment_FireExtinguisher::Start()
{
	GetFBXMesh()->SetFBXMesh("m_sk_fire_extinguisher_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}
