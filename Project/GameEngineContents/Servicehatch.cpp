#include "PreCompile.h"
#include "Servicehatch.h"

Servicehatch::Servicehatch()
{
}

Servicehatch::~Servicehatch()
{
}

void Servicehatch::Start()
{
	GamePlayStaticObject::Start();

	GetCollisionObject()->GetTransform().SetWorldScale({ 200, 50, 200 });
	GetCollisionObject()->GetTransform().SetWorldMove({ -60, 25, 0 });

	GetFBXMesh()->SetFBXMesh("m_dlc08_servicehatch_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	GetFBXMesh()->GetTransform().SetWorldMove({ -60, 0, 0 });
}
