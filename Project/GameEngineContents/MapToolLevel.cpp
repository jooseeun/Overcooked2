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

	// 생성 가능한 UnSortActor 
	Window_->GetAllUnSortActorName().push_back("Chef");
	// 테스트용

	Window_->GetAllUnSortActorName().push_back("Collision_Wall");
	Window_->GetAllUnSortActorName().push_back("Collision_Floor");
	Window_->GetAllUnSortActorName().push_back("MoveNPC_Beard_Orange_01");
	Window_->GetAllUnSortActorName().push_back("MoveNPC_Beard_Waiter_01");
	Window_->GetAllUnSortActorName().push_back("MoveNPC_Dora_Civ_01");
	Window_->GetAllUnSortActorName().push_back("MoveNPC_Hispanic_Yellow_01");
	Window_->GetAllUnSortActorName().push_back("MoveNPC_Mike_Civ_01");
	Window_->GetAllUnSortActorName().push_back("NPC_Asian_Blue_01");
	Window_->GetAllUnSortActorName().push_back("NPC_Beard_Green_01");
	Window_->GetAllUnSortActorName().push_back("NPC_Beard_Waiter_01");
	Window_->GetAllUnSortActorName().push_back("NPC_Beard_Yellow_01");
	Window_->GetAllUnSortActorName().push_back("NPC_Dora_Civ_01");
	Window_->GetAllUnSortActorName().push_back("NPC_Dora_Orange_01");
	Window_->GetAllUnSortActorName().push_back("NPC_DoraBlonde_Blue_01");
	Window_->GetAllUnSortActorName().push_back("NPC_DoraBlonde_Green_01");
	Window_->GetAllUnSortActorName().push_back("NPC_DoraBlonde_Orange_01");
	Window_->GetAllUnSortActorName().push_back("NPC_DoraBlonde_Wizard_01");
	Window_->GetAllUnSortActorName().push_back("NPC_DoraBlonde_Yellow_01");
	Window_->GetAllUnSortActorName().push_back("NPC_Ginger_Blue_01");
	Window_->GetAllUnSortActorName().push_back("NPC_Hispanic_Brown_01");
	Window_->GetAllUnSortActorName().push_back("NPC_Hispanic_Orange_01");
	Window_->GetAllUnSortActorName().push_back("NPC_Hispanic_Wizard_01");
	Window_->GetAllUnSortActorName().push_back("NPC_MiddleEastern_Waiter_01");
	Window_->GetAllUnSortActorName().push_back("NPC_MiddleEatern_Green_01");
	Window_->GetAllUnSortActorName().push_back("NPC_MiddleEatern_Orange_01");
	Window_->GetAllUnSortActorName().push_back("NPC_MiddleEatern_Wizard_01");
	Window_->GetAllUnSortActorName().push_back("NPC_Mike_Blue_01");
	Window_->GetAllUnSortActorName().push_back("NPC_Mike_Wizard_01");
	Window_->GetAllUnSortActorName().push_back("NPC_Mike_Yellow_01");
	Window_->GetAllUnSortActorName().push_back("exterior_car_blue_02");
	Window_->GetAllUnSortActorName().push_back("exterior_car_green_01");
	Window_->GetAllUnSortActorName().push_back("exterior_car_yellow_01");
	Window_->GetAllUnSortActorName().push_back("Candle1Position");
	Window_->GetAllUnSortActorName().push_back("Candle2Position");
	Window_->GetAllUnSortActorName().push_back("Candle3Position");
	Window_->GetAllUnSortActorName().push_back("exterior_grass_01");
	Window_->GetAllUnSortActorName().push_back("m_kevin_01");
	Window_->GetAllUnSortActorName().push_back("m_city_pigeon_01");
	Window_->GetAllUnSortActorName().push_back("traffic_light_animated_01");
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
