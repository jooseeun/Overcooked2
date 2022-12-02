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
	GetMainCameraActorTransform().SetLocalPosition({ -1400, 2300, 1600 });
	// 생성 가능한 UnSortActor 
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
	Window_->GetAllUnSortActorName().push_back("NPC_WizBoy_Blue_01");
	Window_->GetAllUnSortActorName().push_back("NPC_Beard_Brown_01");
	Window_->GetAllUnSortActorName().push_back("NPC_Mike_Brown_01");
	Window_->GetAllUnSortActorName().push_back("Candle1Position");
	Window_->GetAllUnSortActorName().push_back("Candle2Position");
	Window_->GetAllUnSortActorName().push_back("Candle3Position");
	Window_->GetAllUnSortActorName().push_back("exterior_grass_01");
	Window_->GetAllUnSortActorName().push_back("m_kevin_01");
	Window_->GetAllUnSortActorName().push_back("m_city_pigeon_01");
	Window_->GetAllUnSortActorName().push_back("traffic_light_animated_01");
	Window_->GetAllUnSortActorName().push_back("Bamboo2");
	Window_->GetAllUnSortActorName().push_back("Car_Blue");
	Window_->GetAllUnSortActorName().push_back("Car_Bluegreen");
	Window_->GetAllUnSortActorName().push_back("Car_Green");
	Window_->GetAllUnSortActorName().push_back("Car_Yellow");
	Window_->GetAllUnSortActorName().push_back("m_city_liftplatform_01");
	Window_->GetAllUnSortActorName().push_back("Portal_Blue");
	Window_->GetAllUnSortActorName().push_back("Portal_Purple");

	// 2-1
	Window_->GetAllUnSortActorName().push_back("m_dlc09_iceplatform_0");
	Window_->GetAllUnSortActorName().push_back("NPC_Dora_Green_01");
	Window_->GetAllUnSortActorName().push_back("p_dlc09_iceblock_02 (1)");
	Window_->GetAllUnSortActorName().push_back("p_dlc09_iceblock_02 (2)");
	Window_->GetAllUnSortActorName().push_back("p_dlc09_iceblock_02 (3)");
	Window_->GetAllUnSortActorName().push_back("p_dlc09_iceblock_02 (4)");
	Window_->GetAllUnSortActorName().push_back("p_dlc09_iceblock_02 (6)");
	Window_->GetAllUnSortActorName().push_back("p_dlc09_iceblock_02 (8)");
	Window_->GetAllUnSortActorName().push_back("p_dlc09_iceblock_02 (10)");
	Window_->GetAllUnSortActorName().push_back("p_dlc09_iceblock_02 (1)");
	Window_->GetAllUnSortActorName().push_back("RobinGround_01");
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
