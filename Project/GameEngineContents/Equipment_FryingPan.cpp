#include "PreCompile.h"
#include "Equipment_FryingPan.h"

Equipment_FryingPan::Equipment_FryingPan() 
{
}

Equipment_FryingPan::~Equipment_FryingPan() 
{
}

void Equipment_FryingPan::Start()
{
	GamePlayBowl::Start();
	GamePlayBowl::SetToolInfoType(ToolInfo::FryingPan);

}