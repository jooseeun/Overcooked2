#include "PreCompile.h"
#include "MapToolLevel.h"
#include "IOManagerWindow.h"

MapToolLevel::MapToolLevel() 
{
}

MapToolLevel::~MapToolLevel() 
{
}

void MapToolLevel::Start()
{
	Window_ = MapEditorGUI::CreateGUIWindow<MapEditorWindow>("MapEditor", nullptr);

	IOWindow_ = MapEditorGUI::CreateGUIWindow<IOManagerWindow>("IOManager", nullptr);

	Window_->SetLevel(this);
	Window_->Off();

	GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	GetMainCameraActorTransform().SetLocalPosition({ 0, 2000, 1800 });

	// Å×½ºÆ®
	//Window_->GetAllUnSortActorName().push_back("Chef");
	//Window_->GetAllUnSortActorName().push_back("Collision");
}

void MapToolLevel::Update(float _DeltaTime)
{
}

void MapToolLevel::End()
{
}

void MapToolLevel::LevelStartEvent()
{
	Window_->On();
}

void MapToolLevel::LevelEndEvent()
{
	Window_->Off();
}
