#include "PreCompile.h"
#include "Equipment_FireExtinguisher.h"

Equipment_FireExtinguisher::Equipment_FireExtinguisher() 
{
}

Equipment_FireExtinguisher::~Equipment_FireExtinguisher() 
{
}

void Equipment_FireExtinguisher::Start()
{
	GamePlayEquipment::Start();
	GamePlayEquipment::SetToolInfoType(ToolInfo::FireExtinguisher);
}

Input_PickUpOption Equipment_FireExtinguisher::Input_PickUp(std::shared_ptr<Player> _Player)
{
	//_Player->
	return Input_PickUpOption::PickUp;
}