#include "PreCompile.h"
#include "PlateReturn.h"

PlateReturn::PlateReturn() 
{
}

PlateReturn::~PlateReturn() 
{
}

void PlateReturn::Start()
{
	GamePlayStaticObject::Start();

	GetCollisionObject()->GetTransform().SetWorldScale({ 120, 50, 120 });
	GetCollisionObject()->GetTransform().SetWorldMove({ 0, 25, 0 });

	GetFBXMesh()->SetFBXMesh("m_sk_plate_return_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	GetFBXMesh()->GetTransform().SetWorldMove({ 0, 0, 0 });
}

