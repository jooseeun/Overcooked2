#include "PreCompile.h"
#include "MapToolLevel.h"

MapToolLevel::MapToolLevel() 
{
}

MapToolLevel::~MapToolLevel() 
{
}

void MapToolLevel::Start()
{
	Window_ = MapEditorGUI::CreateGUIWindow<MapEditorWindow>("MapEditor", nullptr);

	Window_->SetLevel(this);
	Window_->Off();

	GetMainCameraActorTransform().SetLocalRotation({ 60, 180, 0 });
	GetMainCameraActorTransform().SetLocalPosition({ 0, 2000, 1800 });

	//////////////////////////////////////////////////////////////////////////
	//GamePlayMapObject* Object0 = CreateActor<GamePlayMapObject>();
	//Object0->SetName("Chef");
	//Window_->GetUnSortActorList().push_back(Object0);

	//GamePlayMapObject* Object1 = CreateActor<GamePlayMapObject>();
	//Object1->SetName("Chef");
	//Window_->GetUnSortActorList().push_back(Object1);

	//GamePlayMapObject* Object2 = CreateActor<GamePlayMapObject>();
	//Object2->SetName("Chef");
	//Window_->GetUnSortActorList().push_back(Object2);

	//GamePlayMapObject* Collision = CreateActor<GamePlayMapObject>();
	//Collision->SetName("Collision");
	//Window_->GetUnSortActorList().push_back(Collision);


	// Å×½ºÆ®
	Window_->GetAllUnSortActorName().push_back("Chef");
	Window_->GetAllUnSortActorName().push_back("Collision");
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
