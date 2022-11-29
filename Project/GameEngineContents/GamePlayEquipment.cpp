#include "PreCompile.h"
#include "GamePlayEquipment.h"

GamePlayEquipment::GamePlayEquipment() 
	: Enum_ObjectEquipmentType_(ObjectEquipmentType::None)
{
}

GamePlayEquipment::~GamePlayEquipment() 
{
}

void GamePlayEquipment::Start()
{
	GamePlayMoveable::Start();
	GamePlayMoveable::SetObjectMoveableType(ObjectMoveableType::Equipment);
}


