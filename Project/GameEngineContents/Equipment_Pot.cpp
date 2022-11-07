#include "PreCompile.h"
#include "Equipment_Pot.h"

Equipment_Pot::Equipment_Pot() 
{
}

Equipment_Pot::~Equipment_Pot() 
{
}

void Equipment_Pot::Start()
{
	GamePlayBowl::Start();
	GamePlayBowl::SetToolInfoType(ToolInfo::Pot);

}