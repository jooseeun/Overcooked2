#include "PreCompile.h"
#include "Sink.h"
#include "Equipment_Plate.h"
Sink::Sink()
{
}

Sink::~Sink()
{
}

void Sink::SetSinkMesh(SinkType _Type)
{
	switch (_Type)
	{
	case SinkType::Normal:
		GetFBXMesh()->SetFBXMesh("m_sk_sink_01.fbx", "Texture");
		GetFBXMesh()->GetTransform().SetWorldMove({ -60, 0, 0 });
		break;
	case SinkType::Wizard:
		GetFBXMesh()->SetFBXMesh("m_wizard_sink_01.fbx", "Texture");
		GetFBXMesh()->GetTransform().SetWorldMove({ -60, 70, 0 });
		break;
	default:
		break;
	}

	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

void Sink::Start()
{
	GamePlayStaticObject::Start();


	GetCollisionObject()->GetTransform().SetWorldScale({ 230, 50, 150 });
	GetCollisionObject()->GetTransform().SetWorldMove({ -60, 25, -10 });
}
