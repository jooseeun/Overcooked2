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
	GetCollisionObject()->ChangeOrder(CollisionOrder::Object_StaticObject);

	ToolPos_ = GetTransform().GetWorldPosition() + float4{0, 30.f};
}

void GamePlayStaticObject::SetBloomEffectOff()
{
	GamePlayObject::SetBloomEffectOff();
	if (Stuff_Current_ != nullptr)
	{
		Stuff_Current_->SetBloomEffectOff();
	}

}

void GamePlayStaticObject::SetBloomEffectOn()
{
	GamePlayObject::SetBloomEffectOn();
	if (Stuff_Current_ != nullptr)
	{
		Stuff_Current_->SetBloomEffectOn();
	}
}

Input_PickUpOption GamePlayStaticObject::Input_PickUp(std::shared_ptr<GamePlayMoveable> _Object)
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

Input_PickUpOption GamePlayStaticObject::Input_PickUp(std::shared_ptr<Player> _Player)
{
	if (Stuff_Current_ != nullptr)
	{
		if (Stuff_Current_->Input_PickUp(_Player) == Input_PickUpOption::PickUp)
		{
			Stuff_Current_ = nullptr;
			return Input_PickUpOption::PickUp;
		}
		else
		{
			return Input_PickUpOption::NoResponse;
		}
	}
	else
	{
		return Input_PickUpOption::NoResponse;
	}

}