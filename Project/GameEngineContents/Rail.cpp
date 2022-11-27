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

void Rail::Update(float _Delta)
{
	GetFBXMesh()->RenderOptionInst.UV.x += _Delta;
}


Tool_Rail::Tool_Rail()
{
}

Tool_Rail::~Tool_Rail()
{
}
void Tool_Rail::Start()
{
	GamePlayTool::Start();
	GamePlayTool::SetInteractOption(AutoOption::NoResponse);
	GamePlayTool::SetObjectToolType(ObjectToolType::Rail);
}


