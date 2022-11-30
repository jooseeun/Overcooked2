#include "PreCompile.h"
#include "Tool_Mixer.h"

Tool_Mixer::Tool_Mixer() 
{
}

Tool_Mixer::~Tool_Mixer() 
{
}

void Tool_Mixer::Start()
{
	GamePlayTool::Start();
	GamePlayTool::SetInteractOption(AutoOption::Manual);
	GamePlayTool::SetToolInfoType(ToolInfo::Mixer);
	GamePlayTool::SetObjectToolType(ObjectToolType::Mixer);

	GetAnimationFBXMesh()->SetFBXMesh("m_cakemixer_Body_01.fbx", "TextureAnimation");
	GetAnimationFBXMesh()->GetTransform().SetWorldScale({ 100, 100, 100 });

	GetAnimationFBXMesh()->GetTransform().SetLocalRotation({0, 90, 0});
	//GetAnimationFBXMesh()->GetTransform().SetLocalPosition({0, -50, 0});

	GetAnimationFBXMesh()->CreateFBXAnimation("Idle", GameEngineRenderingEvent("m_cakemixer_Body_01.fbx", 0.01f, true));
	GetAnimationFBXMesh()->ChangeAnimation("Idle");
}

