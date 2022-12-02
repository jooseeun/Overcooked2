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

	GetCollisionObject()->GetTransform().SetWorldScale({ 230, 50, 150 });
	GetCollisionObject()->GetTransform().SetWorldMove({ -60, 25, -10 });

	GetFBXMesh()->SetFBXMesh("m_dlc08_servicehatch_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
	GetFBXMesh()->GetTransform().SetWorldMove({ -60, 0, 0 });
	
	GetFBXMesh()->SetSubConstantBufferLink(0, "RENDEROPTION", &RenderOptionMyInst, sizeof(RenderOption));
}

void Servicehatch::Update(float _DeltaTime)
{
	RenderOptionMyInst.UV.x -= _DeltaTime * 0.5f;
}


Tool_Servicehatch::Tool_Servicehatch()
{
}

Tool_Servicehatch::~Tool_Servicehatch()
{
}
void Tool_Servicehatch::Start()
{
	GamePlayTool::Start();
	GamePlayTool::SetInteractOption(AutoOption::NoResponse);
	GamePlayTool::SetObjectToolType(ObjectToolType::Servicehatch);
}


