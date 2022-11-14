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

Input_PickUpOption GamePlayEquipment::Input_PickUp(std::shared_ptr<Player> _Player)
{
	_Player->SetCurHoldType(PlayerHoldType::FireExtinguisher);
	return Input_PickUpOption::PickUp;
}