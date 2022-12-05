#include "PreCompile.h"
#include "GamePlayEquipment.h"
#include "GamePlayTool.h"

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
	GamePlayMoveable::SetHoldType(PlayerHoldType::NotThrow);
}


HoldDownEnum GamePlayEquipment::PickUp(std::shared_ptr<GamePlayMoveable>* _Moveable)
{
	if ((*_Moveable) == nullptr)
	{
		(*_Moveable) = CastThis<GamePlayMoveable>();
		return HoldDownEnum::HoldDown;
	}
	return HoldDownEnum::Nothing;
}