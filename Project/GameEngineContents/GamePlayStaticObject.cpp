#include "PreCompile.h"
#include "GamePlayStaticObject.h"
#include "GamePlayStuff.h"
#include "GamePlayMoveable.h"
#include "GamePlayTool.h"

GamePlayStaticObject::GamePlayStaticObject() 
	: Stuff_Current_(nullptr)
	, ToolPos_(float4::ZERO)
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
		Input_PickUpOption Option = Stuff_Current_->Input_PickUp(_Player);
		if (Option == Input_PickUpOption::PickUp)
		{
			_Player->Input_PickUp(std::dynamic_pointer_cast<GamePlayMoveable>(Stuff_Current_));
			Stuff_Current_.reset();
			return Input_PickUpOption::PickUp;
		}
		else if (Option == Input_PickUpOption::Exception)
		{
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

std::shared_ptr<GamePlayMoveable> GamePlayStaticObject::GetMoveable() const
{
	if (Stuff_Current_ == nullptr)
	{
		return nullptr;
	}
	else if (Stuff_Current_->GetObjectStuffType() == ObjectStuffType::Moveable)
	{
		return std::dynamic_pointer_cast<GamePlayMoveable>(Stuff_Current_);
	}
	else
	{
		return std::dynamic_pointer_cast<GamePlayTool>(Stuff_Current_)->GetCurrentMoveable();
	}
}