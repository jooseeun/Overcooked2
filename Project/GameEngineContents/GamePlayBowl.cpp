#include "PreCompile.h"
#include "GamePlayBowl.h"
#include "GamePlayFood.h"

GamePlayBowl::GamePlayBowl() 
{
}

GamePlayBowl::~GamePlayBowl() 
{
}

void GamePlayBowl::Start()
{
	GamePlayEquipment::Start();
	GamePlayEquipment::SetObjectEquipmentType(ObjectEquipmentType::Bowl);
}

