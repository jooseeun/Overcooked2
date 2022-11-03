#include "PreCompile.h"
#include "GamePlayTool.h"
#include "GamePlayMoveable.h"

GamePlayTool::GamePlayTool() 
	: Food_Current_(nullptr)
	, CookingGage(0)
{
}

GamePlayTool::~GamePlayTool() 
{
}

// ---------------------------------------Start
void GamePlayTool::Start()
{
	GamePlayStuff::Start();
	GamePlayStuff::SetObjectStuffType(ObjectStuffType::Tool);

}

Input_PickUpOption GamePlayTool::Input_PickUp(GamePlayMoveable* _Object)
{
	if (Food_Current_ == nullptr)
	{	
		if (CheckMoveable(_Object) == Input_PickUpOption::PickUp)
		{
			Food_Current_ = _Object;
			return Input_PickUpOption::PickUp;
		}
		else
		{
			return Input_PickUpOption::NoResponse;
		}

	}
	else
	{
		return Food_Current_->Input_PickUp(_Object);
	}
}
// ---------------------------------------Update
//void GamePlayTool::Update(float _DeltaTime)
//{
//
//}