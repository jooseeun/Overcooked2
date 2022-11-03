#include "PreCompile.h"
#include "MeshToolLevel.h"
#include "MeshEditorGUI.h"

MeshToolLevel::MeshToolLevel() 
{
}

MeshToolLevel::~MeshToolLevel() 
{
}


void MeshToolLevel::Start()
{
	MeshSelectWindow_ = MeshEditorGUI::CreateGUIWindow<MeshSelectWindow>("MeshSelectWindow", nullptr);
	MeshSelectWindow_->Off();
}

void MeshToolLevel::Update(float _DeltaTime)
{
}

void MeshToolLevel::End()
{
}

void MeshToolLevel::LevelStartEvent()
{
	MeshSelectWindow_->On();
}

void MeshToolLevel::LevelEndEvent()
{
	MeshSelectWindow_->Off();

}
