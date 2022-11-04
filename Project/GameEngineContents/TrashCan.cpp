#include "PreCompile.h"
#include "TrashCan.h"

TrashCan::TrashCan() 
{
}

TrashCan::~TrashCan() 
{
}

void TrashCan::Start()
{
	GamePlayStaticObject::Start();

	GetCollisionObject()->GetTransform().SetWorldScale({ 100, 50, 100 });
	GetCollisionObject()->GetTransform().SetWorldMove({ 0, 25, 0 });

	GetFBXMesh()->SetFBXMesh("m_sk_bin_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

