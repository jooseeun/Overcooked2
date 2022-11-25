#include "PreCompile.h"
#include "Equipment_FryingPan.h"

Equipment_FryingPan::Equipment_FryingPan() 
{
}

Equipment_FryingPan::~Equipment_FryingPan() 
{
}

void Equipment_FryingPan::Start()
{
	GetFBXMesh()->SetFBXMesh("m_sk_fryingpan_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

