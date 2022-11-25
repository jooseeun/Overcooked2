#include "PreCompile.h"
#include "Equipment_Plate.h"

Equipment_Plate::Equipment_Plate()

{
}

Equipment_Plate::~Equipment_Plate() 
{
}

void Equipment_Plate::Start()
{
	GetFBXMesh()->SetFBXMesh("m_sk_plate_02.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	GetCollisionObject()->GetTransform().SetWorldPosition({ 0, -25, 0});
	GetCollisionObject()->GetTransform().SetLocalScale({ 100, 25, 100 });
}
