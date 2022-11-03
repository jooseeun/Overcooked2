#include "PreCompile.h"
#include "GamePlayStaticObject.h"
#include "GamePlayStuff.h"
#include "GamePlayMoveable.h"

GamePlayStaticObject::GamePlayStaticObject() 
	: Stuff_Current_(nullptr)
{
}

GamePlayStaticObject::~GamePlayStaticObject() 
{
}

void GamePlayStaticObject::Start()
{
	GamePlayObject::Start();
	GamePlayObject::SetObjectType(ObjectType::StaticObject);
}

Input_PickUpOption GamePlayStaticObject::Input_PickUp(GamePlayMoveable* _Object)
{
	if (Stuff_Current_ != nullptr)
	{
		return Stuff_Current_->Input_PickUp(_Object);
	}
	else
	{
		Stuff_Current_ = _Object;
		return Input_PickUpOption::PickUp;
	}

}