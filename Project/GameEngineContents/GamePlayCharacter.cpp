#include "PreCompile.h"
#include "GamePlayCharacter.h"

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
}

void GamePlayCharacter::Collision_AroundObject()
{
	if (Collision_Interact_->IsCollision(CollisionType::CT_SPHERE, CollisionOrder::Object_Moveable, CollisionType::CT_SPHERE, 
		std::bind(&GamePlayCharacter::GetCrashObject, this, std::placeholders::_1, std::placeholders::_2)))
	{

	}
}

CollisionReturn GamePlayCharacter::GetCrashObject(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	_Other->GetActor<GamePlayObject>();
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