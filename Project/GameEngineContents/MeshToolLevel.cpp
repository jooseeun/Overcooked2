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
	GetMainCameraActorTransform().SetWorldPosition({2.f, 200.f, -900.f});

}

void MeshToolLevel::LevelEndEvent()
{
	MeshSelectWindow_->Off();

}
