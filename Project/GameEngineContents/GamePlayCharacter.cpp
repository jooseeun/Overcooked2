#include "PreCompile.h"
#include "GamePlayCharacter.h"
#include "GamePlayStaticObject.h"
#include "GamePlayMoveable.h"

GamePlayCharacter::GamePlayCharacter()
	: Moveable_Current_(nullptr)
	, Collision_Interact_(nullptr)
	, Interact_Possible_Object_(nullptr)
	, Interact_Possible_StaticObject_(nullptr)
{
}

GamePlayCharacter::~GamePlayCharacter()
{
}

void GamePlayCharacter::Start()
{
	GamePlayObject::Start();
	GamePlayObject::SetObjectType(ObjectType::Character);
	Collision_Interact_ = CreateComponent<GameEngineCollision>("PlayerCollision");
	Collision_Interact_->SetDebugSetting(CollisionType::CT_SPHERE, {0.8f, 0, 0, 0.7f});
	GetCollisionObject()->ChangeOrder(CollisionOrder::Object_Character);

	if (GameEngineInput::GetInst()->IsKey("Interaction"))
	{
		GameEngineInput::GetInst()->CreateKey("Interaction", VK_SPACE);
	}
}



void GamePlayCharacter::Collision_AroundObject()
{
	if (Moveable_Current_ == nullptr &&
		Collision_Interact_->IsCollision(CollisionType::CT_SPHERE, CollisionOrder::Object_Moveable, CollisionType::CT_SPHERE, 
		std::bind(&GamePlayCharacter::GetCrashMoveableObject, this, std::placeholders::_1, std::placeholders::_2)))
	{
		if (GameEngineInput::GetInst()->IsDownKey("Interaction"))
		{
			if (Moveable_Current_ == nullptr &&
				Interact_Possible_Object_->Input_PickUp(this) == Input_PickUpOption::PickUp)
			{
				Interact_Possible_Object_ = nullptr;
			}
			else
			{

			}

			return;
		}
	}
	else
	{
		if (Interact_Possible_Object_ != nullptr)
		{
			Interact_Possible_Object_->SetBloomEffectOff();
			Interact_Possible_Object_ = nullptr;
		}
	}



	if (Collision_Interact_->IsCollision(CollisionType::CT_SPHERE, CollisionOrder::Object_StaticObject, CollisionType::CT_SPHERE,
		std::bind(&GamePlayCharacter::GetCrashStaticObject, this, std::placeholders::_1, std::placeholders::_2)))
	{
		if (GameEngineInput::GetInst()->IsDownKey("Interaction"))
		{

		}
	}
	else
	{
		if (Interact_Possible_StaticObject_ != nullptr)
		{
			Interact_Possible_StaticObject_->SetBloomEffectOff();
			Interact_Possible_StaticObject_ = nullptr;
		}
	}

}

CollisionReturn GamePlayCharacter::GetCrashMoveableObject(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (Interact_Possible_Object_ != nullptr)
	{
		Interact_Possible_Object_->SetBloomEffectOff();
		//Interact_Possible_StaticObject_ = nullptr;
	}

	Interact_Possible_Object_ = _Other->GetActor<GamePlayMoveable>();
	Interact_Possible_Object_->SetBloomEffectOn();
	return CollisionReturn::Break;
}

CollisionReturn GamePlayCharacter::GetCrashStaticObject(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (Interact_Possible_StaticObject_ != nullptr)
	{
		Interact_Possible_StaticObject_->SetBloomEffectOff();
		//Interact_Possible_StaticObject_ = nullptr;
	}
	Interact_Possible_StaticObject_ = _Other->GetActor<GamePlayStaticObject>();
	Interact_Possible_StaticObject_->SetBloomEffectOn();
	return CollisionReturn::Break;
}

void GamePlayCharacter::Input_PickUpButton()
{
	if (Moveable_Current_ == nullptr)
	{

	}
	else
	{

	}
}