#include "PreCompile.h"
#include "Mixer.h"
#include "Equipment_Bowl.h"

Mixer::Mixer()
	: MyType_(MixerType::Max)
{
}

Mixer::~Mixer()
{
}

void Mixer::Start()
{
	GamePlayStaticObject::Start();

	GetCollisionObject()->GetTransform().SetWorldScale({ 120, 50, 120 });
	GetCollisionObject()->GetTransform().SetWorldMove({ 0, 25, 0 });

}

void Mixer::SetMixerMesh(MixerType _Type)
{
	std::string Name = "";

	switch (_Type)
	{
	case MixerType::Mixer_Kevin:
		Name = "CounterMixer2.fbx";
		break;
	case MixerType::Mixer_Winter:
		Name = "CounterMixer_Winter.fbx";
		break;
	default:
		break;
	}

	GetFBXMesh()->SetFBXMesh(Name, "Texture");
	GetFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });
}

Tool_Mixer::Tool_Mixer() 
{
}

Tool_Mixer::~Tool_Mixer() 
{
}


// ----------------------Tool---------------------------

void Tool_Mixer::Start()
{
	GamePlayTool::Start();
	GamePlayTool::SetInteractOption(AutoOption::Manual);
	GamePlayTool::SetToolInfoType(ToolInfo::Mixer);
	GamePlayTool::SetObjectToolType(ObjectToolType::Mixer);

	SetMoveable(GetLevel()->CreateActor<Equipment_Bowl>());
}

