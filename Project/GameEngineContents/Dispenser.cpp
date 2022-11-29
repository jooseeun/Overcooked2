#include "PreCompile.h"
#include "Dispenser.h"

Dispenser::Dispenser() 
{
}

Dispenser::~Dispenser() 
{
}

void Dispenser::Start()
{
	GamePlayStaticObject::Start();

	GetFBXMesh()->SetFBXMesh("m_city_dispenser_01.fbx", "Texture");
	GetFBXMesh()->GetTransform().SetWorldMove({0.f, 0.f, -50.f});

	GetCollisionObject()->GetTransform().SetWorldScale({ 120, 50, 120 });
	GetCollisionObject()->GetTransform().SetWorldMove({ 0, 25, 0 });
}

void Dispenser::Update(float _DeltaTime)
{
}


Tool_Dispenser::Tool_Dispenser()
{
}

Tool_Dispenser::~Tool_Dispenser()
{
}
void Tool_Dispenser::Start()
{
	GamePlayTool::Start();
	GamePlayTool::SetInteractOption(AutoOption::NoResponse);
	GamePlayTool::SetObjectToolType(ObjectToolType::Dispenser);
}
