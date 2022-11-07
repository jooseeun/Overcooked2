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